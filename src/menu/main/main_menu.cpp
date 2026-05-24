#include <memory>
#include "Database.h"
#include "db/db_menu.h"
#include "main_menu_render.h"
#include "rect.h"
#include "term.h"
#include "main_menu.h"
#include "option_menu.h"
#include "help/help.h"


void MainMenu::init(){
	Database db("/home/hvidal/db.txt");
	db.load("123");

	int width;
	int height;
	term.get_sizes(width,height);
	screen = {0,0,width,height};

	int gap = 1;
	int x = 2;


	Rect tabbar_rect = {x, 
		2, 
		screen.width - tabbar_rect.x*2, 
		2};

	Rect help_rect = {x,
		screen.height - x - 1,
		screen.width - help_rect.x*2,
		1};

	Rect db_rect = {x, 
		tabbar_rect.y + tabbar_rect.height + gap, 
		screen.width - db_rect.x*2, 
		screen.height - (tabbar_rect.y*2 + tabbar_rect.height + help_rect.height + gap)};


	main_menus.push_back(std::make_unique<OptionMenu>(term, "", names));
	main_rects.push_back(tabbar_rect);

	main_menus.push_back(std::make_unique<DatabaseMenu>(term, db.db_file, db, db.dump()));
	main_rects.push_back(db_rect);

	help_bar.rect = help_rect;

}

void MainMenu::render(){
	term.clear();
	if (main_menus.size() != main_rects.size()) return;

	if (popups_stack.size() > 0)
		focused_menu = -1;

	for (int i = 0; i < main_menus.size(); i++){
		if (i == focused_menu)
			main_menus[i]->render(main_rects[i], true); // focused
		else
			main_menus[i]->render(main_rects[i], false); // unfocused 
	}
	
	if (focused_menu == 0)
		help_bar.render({"tabbar", "opciones", "de", "tabbar"});
	if (focused_menu == 1)
		help_bar.render({"db", "opciones", "de", "db"});
	
	if (popups_stack.size() > 0){
		Rect sizes = popups_stack[0]->preferred_size();
		Rect popup = Layout::centered_rect(screen,sizes.width,sizes.height);
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

