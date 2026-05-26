#include <memory>
#include <string>
#include <vector>
#include "ui/db/db_menu.h"
#include "ui/text/text_menu.h"
#include "ui/number/number_menu.h"
#include "ui/options/option_menu.h"
#include "ui/rect.h"
#include "ui/ui_request.h"
#include "workflows/new_pass_workflow.h"

bool DatabaseMenu::handle_input(char c) {
	switch (c) {
		case '\n':
			if (secondary_selection >= 0){
				if (secondary_selection == 0) term.copy(options[current_selection].user);
				else term.copy(options[current_selection].pass);

				std::string prefix;
				if (secondary_selection == 0) prefix = "user";
				else if (secondary_selection == 1) prefix = "pass";
				else prefix = "other";

				menu_render.msg(options[current_selection].site + " " + prefix + " copied to clipboard");
			}
			secondary_selection = -(secondary_selection != -1);
			break;
		case KEY_DOWN:
		case 'j':
			select(true);
			break;
		case KEY_UP:
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

void DatabaseMenu::select(bool direction){
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

void DatabaseMenu::new_pass(){
	active_workflow = std::make_unique<NewPassWorkflow>(db);
	active_workflow->start();
}

void DatabaseMenu::filter(){
	TextMenu site_menu(term, "Site");
	site_menu.start();
	options = db.find(site_menu.get_str());
	current_selection = 0;
}

void DatabaseMenu::edit(){
	TextMenu user_menu(term, "New user");
	user_menu.start();
	TextMenu pass_menu(term, "New pass");
	pass_menu.start();

	db.edit(options[current_selection], user_menu.get_str(), pass_menu.get_str());
	db.update_db();
	options = db.dump();
}

void DatabaseMenu::remove(){
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

void DatabaseMenu::sec_pass(){
	NumberMenu number_menu(term, "Number of chars");
	number_menu.start();
	menu_render.draw_sec_pass(number_menu.get_value());
}

int DatabaseMenu::get_value() {
	return current_selection;
}

void DatabaseMenu::render(Rect rect, bool focused) {
	menu_render.configure_render(current_selection, secondary_selection, focused);
	menu_render.render(rect, focused);
}

void DatabaseMenu::pull_result(const std::string result) {
	if (!active_workflow)
		return;

	active_workflow->pull_result(result);
	if (active_workflow->finished()) {
		options = db.dump();
		active_workflow.reset();
	}
}

Ui_request DatabaseMenu::pull_request() {
	if (!active_workflow)
		return Ui_request{Ui_request::NONE};
	return active_workflow->pull_request();
}
