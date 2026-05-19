#include "menu.h"

void Menu::start(){
	// term.clear();
	term.hide_cursor();
	bool runing = true;
	render();

	while (runing){
		char c = term.read_char();
		runing = handle_input(c);
		render();
	}

	end();
}

void Menu::end(){
	term.hide_cursor();
	// term.clear();
}
