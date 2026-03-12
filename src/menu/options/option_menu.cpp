#include "option_menu.h"

void OptionMenu::select(bool direction){
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

bool OptionMenu::handle_input(char c) {
	if (c == ENTER){
		return false;
	}

	if (c == KEY_RIGHT){
		select(true);
	}
	else if (c == KEY_LEFT){
		select(false);
	}
	return true;
}

int OptionMenu::get_value() {
	return current_selection;
}

void OptionMenu::render(){
	menu_render.render(title, options, current_selection);
}
