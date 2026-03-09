#include "main_menu.h"
#include "text_menu.h"

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

bool MainMenu::handle_input(char c) {
	if (c == ESC){
		return false;
	} else if (c == KEY_DOWN || c == 'j'){
		select(true);
	} else if (c == KEY_UP || c == 'k'){
		select(false);
	} else if (c == 'n'){
		new_pass();
	}
	return true;
}

int MainMenu::get_value() {
	return current_selection;
}

void MainMenu::render(){
	menu_render.render(title, options, current_selection);
}

void MainMenu::new_pass(){
	TextMenu site_menu(term, "site");
	site_menu.start();
	TextMenu user_menu(term, "User");
	user_menu.start();
	TextMenu pass_menu(term, "pass");
	pass_menu.start();

	db.add(site_menu.get_str(), user_menu.get_str(), pass_menu.get_str());
	db.update_db();
	options = db.dump();
}

