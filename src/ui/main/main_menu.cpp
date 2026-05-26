#include <iostream>
#include <memory>
#include "main_menu_render.h"
#include "main_menu.h"

#include "Database.h"
#include "term/term.h"

#include "ui/help/help.h"
#include "ui/ui_request.h"
#include "ui/rect.h"

#include "ui/db/db_menu.h"
#include "ui/options/option_menu.h"
#include "ui/text/text_menu.h"
#include "ui/path/path_menu.h"
#include "ui/number/number_menu.h"
#include "ui/message/message.h"


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

	// main menus
	for (int i = 0; i < main_menus.size(); i++){
		if (i == focused_menu && popups_stack.empty())
			main_menus[i]->render(main_rects[i], true); // focused
		else
			main_menus[i]->render(main_rects[i], false); // unfocused 
	}
	
	// help bar
	if (focused_menu == 0)
		help_bar.render({"tabbar", "opciones", "de", "tabbar"});

	if (focused_menu == 1)
		help_bar.render({"db", "opciones", "de", "db"});
	
	// popups
	if (popups_stack.size() > 0){
		Rect sizes = popups_stack[0]->preferred_size();
		Rect popup = Layout::centered_rect(screen,sizes.width,sizes.height);
		popups_stack[0]->render(popup, true);
	}
}

bool MainMenu::handle_input(char c) {
	if (!popups_stack.empty()){
		bool active = popups_stack[0]->handle_input(c);

		if (!active){
			main_menus[focused_menu]->pull_result(popups_stack[0]->get_str());
			popups_stack.erase(popups_stack.begin());
			pull_request();
		}

		return true;
	}

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
	pull_request();
	return true;
}

void MainMenu::pull_request(){
	Ui_request request = main_menus[focused_menu]->pull_request();

	if (request.type == Ui_request::NONE) return;

	switch (request.type){
		case Ui_request::TEXT:
			popups_stack.push_back(std::make_unique<TextMenu>(term, request.title));
			break;

		case Ui_request::PATH:
			popups_stack.push_back(std::make_unique<PathMenu>(term, request.title, request.options));
			break;

		case Ui_request::MESSAGE:
			popups_stack.push_back(std::make_unique<Message>(term, request.title, request.msg));
			break;

		case Ui_request::NUMBER:
			popups_stack.push_back(std::make_unique<NumberMenu>(term, request.title, request.min_value, request.max_value));
			break;

		case Ui_request::OPTIONS:
			popups_stack.push_back(std::make_unique<OptionMenu>(term, request.title, request.options));
			break;

		default:
			return;
			break;
	}
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

