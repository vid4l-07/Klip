#include "main_menu.h"
#include "../text/text_menu.h"
#include "../number/number_menu.h"
#include "../options/option_menu.h"
#include <string>
#include <vector>

bool MainMenu::handle_input(char c) {
	switch (c) {
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
	if (direction){
		if (current_selection < int(options.size() - 1)){
			current_selection ++;
		}
	} else {
		if (current_selection > 0){
			current_selection --;
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
	OptionMenu confirm_menu(term, "Remove " + options[current_selection].sitio + "?", opts);
	confirm_menu.start();
	int select = confirm_menu.get_value();
	if (select){
		db.remove(current_selection);
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
	menu_render.render(title, options, current_selection);
}

