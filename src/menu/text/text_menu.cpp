#include "text_menu.h"
#include "rect.h"

bool TextMenu::handle_input(char c) {
	switch (c) {
		case ENTER: 
			return false; 
			break;
		case ESC: 
			current_str.clear();
			return false;
			break;
		case KEY_BACKSPACE: 
			if (current_str.size() > 0){
				current_str.pop_back(); 
			}
			break;
		default:
			current_str += c;
			break;
	};
	return true;
}

std::string TextMenu::get_str() {
	return current_str;
}

void TextMenu::render(Rect rect, int border_color) {
	menu_render.configure_render(current_str);
	menu_render.render(rect, border_color);
}
