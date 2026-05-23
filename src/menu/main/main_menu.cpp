#include <memory>
#include "rect.h"
#include "term.h"
#include "main_menu.h"
#include "option_menu.h"

void MainMenu::render(){
	term.clear();
	Rect pos1 = {1,1,0,0};
	Rect pos2 = {1,10,0,0};
	std::vector<Rect> vector = {pos1, pos2};
	for (int i = 0; i < main_menus.size(); i++){
		Rect sizes = main_menus[i] -> preferred_size();
		if (i == focused_menu)
			main_menus[i]->render({vector[i].x,vector[i].y,screen.width - 2,sizes.height}, 34); // focused
		else
			main_menus[i]->render({vector[i].x,vector[i].y,screen.width - 2,sizes.height}, 0); // unfocused 
	}
}

bool MainMenu::handle_input(char c) {
	switch (c){
		case KEY_TAB:  // change window
			focused_menu = (focused_menu + 1) % main_menus.size();
			return true;
			break;

		case 'q':
			return false;
			break;
	}

	main_menus[focused_menu]->handle_input(c);
	return true;
}

void MainMenu::start(){
	term.hide_cursor();
	bool runing = true;
	render();

	while (runing){
		char c = term.read_char();
		runing = handle_input(c);
		render();
	}
	term.end();
}

void MainMenu::init(){
	main_menus.push_back(std::make_unique<OptionMenu>(term, "hola", names));
	main_menus.push_back(std::make_unique<OptionMenu>(term, "hola", names2));

	int width;
	int height;
	term.get_sizes(width,height);
	screen.x = 0;
	screen.y = 0;
	screen.width = width;
	screen.height = height;
}
