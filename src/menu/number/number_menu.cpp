#include "number_menu.h"

bool NumberMenu::handle_input(char c) {
	switch (c){
		case ENTER:
			return false;
			break;
		case KEY_UP:
			if (value < max_value)
				value++;
			break;
		case KEY_DOWN:
			if (value > min_value)
				value--;
			break;
		case KEY_BACKSPACE:{
			int result = value / 10;
			if (result >= min_value){
				value = result;
			}
		}
		default:{
			if (c >= '0' && c <= '9'){
				int num = c - '0';
				int result = value * 10 + num;
				if (result <= max_value){
					value = result;
				}
			}
		}
	}
	return true;
}

int NumberMenu::get_value() {
	return value;
}

void NumberMenu::render(){
	menu_render.render(title, value);
}
