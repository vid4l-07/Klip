#include "text_menu.h"
#include <string>

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
			current_str.pop_back(); 
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

void TextMenu::render(){
	menu_render.render(title, current_str);
}
