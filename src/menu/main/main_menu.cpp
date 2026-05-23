#include <memory>
#include "Database.h"
#include "db/db_menu.h"
#include "rect.h"
#include "term.h"
#include "main_menu.h"
#include "option_menu.h"

void MainMenu::render(){
	term.clear();

	Rect pos1 = {1,8,0,0};
	Rect pos2 = {1,2,0,0};

	std::vector<Rect> vector = {pos1, pos2};

	if (popups_stack.size() > 0)
		focused_menu = -1;

	for (int i = 0; i < main_menus.size(); i++){
		Rect sizes = main_menus[i] -> preferred_size();

		if (i == focused_menu)
			main_menus[i]->render({vector[i].x,vector[i].y,screen.width - 2,sizes.height}, true); // focused
		else
			main_menus[i]->render({vector[i].x,vector[i].y,screen.width - 2,sizes.height}, false); // unfocused 
	}
	
	if (popups_stack.size() > 0){
		Rect sizes = popups_stack[0]->preferred_size();
		Rect popup = layout.centered_rect(screen,sizes.width,sizes.height);
		popups_stack[0]->render(popup, true);
	}
}

bool MainMenu::handle_input(char c) {
	switch (c){
		case KEY_TAB:  // change focus
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
	Database db("/home/hvidal/db.txt");
	db.load("123");
	main_menus.push_back(std::make_unique<DatabaseMenu>(term, db.db_file, db, db.dump()));
	main_menus.push_back(std::make_unique<OptionMenu>(term, "hola", names2));

	int width;
	int height;
	term.get_sizes(width,height);
	screen.x = 0;
	screen.y = 0;
	screen.width = width;
	screen.height = height;
}
