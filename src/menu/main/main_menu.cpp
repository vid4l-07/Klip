#include "main_menu.h"
#include "../text/text_menu.h"
#include "../number/number_menu.h"
#include "../options/option_menu.h"
#include <string>
#include <vector>

bool MainMenu::handle_input(char c) {
	switch (c) {
		case '\n':
			if (secondary_selection >= 0){
				if (secondary_selection == 0) term.copy(options[current_selection].user);
				else term.copy(options[current_selection].pass);

				std::string prefix;
				if (secondary_selection == 0) prefix = "user";
				else if (secondary_selection == 1) prefix = "pass";
				else prefix = "other";

				menu_render.msg("Copied " + options[current_selection].site + " " + prefix + " to clipboard");
			}
			secondary_selection = -(secondary_selection != -1);
			break;
		case 'q':
			return false;
			break;
		case 'j':
			select(true);
			break;
		case 'k':
			select(false);
			break;
		case 'n':
			new_pass();
			break;
		case 'f':
			filter();
			break;
		case 'e':
			edit();
			break;
		case 'd':
			remove();
			break;
		case 'g':
			sec_pass();
			break;
	}
	return true;
}

void MainMenu::select(bool direction){
	int* selection = nullptr;
	int size;
	if (secondary_selection < 0) {
		size = options.size();
		selection = &current_selection; 
	}
	else {
		size = 2;
		selection = &secondary_selection; 
	}

	if (direction){
		if (*selection < size - 1){
			(*selection) ++;
		}
	} else {
		if (*selection > 0){
			(*selection) --;
		}
	}
}

void MainMenu::new_pass(){
	TextMenu site_menu(term, "Site");
	site_menu.start();
	TextMenu user_menu(term, "User");
	user_menu.start();
	TextMenu pass_menu(term, "Pass");
	pass_menu.start();

	db.add(site_menu.get_str(), user_menu.get_str(), pass_menu.get_str());
	db.update_db();
	options = db.dump();
}

void MainMenu::filter(){
	TextMenu site_menu(term, "Site");
	site_menu.start();
	options = db.find(site_menu.get_str());
	current_selection = 0;
}

void MainMenu::edit(){
	TextMenu user_menu(term, "New user");
	user_menu.start();
	TextMenu pass_menu(term, "New pass");
	pass_menu.start();

	db.edit(current_selection, user_menu.get_str(), pass_menu.get_str());
	db.update_db();
	options = db.dump();
}

void MainMenu::remove(){
	std::vector<std::string> opts = {"no", "yes"};
	OptionMenu confirm_menu(term, "Remove " + options[current_selection].site + "?", opts);
	confirm_menu.start();
	int select = confirm_menu.get_value();
	if (select){
		db.remove(options[current_selection]);
		db.update_db();
		options = db.dump();
	}
	current_selection = 0;
}

void MainMenu::sec_pass(){
	NumberMenu number_menu(term, "Number of chars");
	number_menu.start();
	menu_render.draw_sec_pass(number_menu.get_value());
}

int MainMenu::get_value() {
	return current_selection;
}

void MainMenu::render(){
	menu_render.render(title, options, current_selection, secondary_selection);
}

