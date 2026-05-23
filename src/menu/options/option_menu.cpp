#include "option_menu.h"
#include "rect.h"

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
	switch (c){
		case ENTER:
			return false;
			break;
		case 'l':
		case KEY_RIGHT:
			select(true);
			break;
		case 'h':
		case KEY_LEFT:
			select(false);
			break;
	}
	return true;
}

int OptionMenu::get_value() {
	return current_selection;
}

void OptionMenu::render(Rect rect, int border_color) {
	menu_render.configure_render(current_selection);
	menu_render.render(rect, border_color);
}
