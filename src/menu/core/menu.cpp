#include "menu.h"

void Menu::start(){
	term.clear();
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
	term.clear();
}
