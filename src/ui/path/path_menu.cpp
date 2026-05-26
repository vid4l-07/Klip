#include "path_menu.h"

bool PathMenu::handle_input(char c) {
	switch (c) {
		case KEY_TAB: 
			if (options.size() != 0){
				current_str = options[count];
				count = (count + 1) % options.size();
			}
			return true;
			break;
	}
	return TextMenu::handle_input(c);
}

