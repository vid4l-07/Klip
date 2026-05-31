#include <memory>
#include "layout.h"
#include "app.h"

#include "db/database.h"
#include "term/term.h"

#include "ui/help/help.h"
#include "ui/ui_request.h"
#include "ui/rect.h"

#include "ui/db/db_menu.h"
#include "ui/tabbar/tabbar.h"
#include "ui/options/option_menu.h"
#include "ui/text/text_menu.h"
#include "ui/path/path_menu.h"
#include "ui/number/number_menu.h"
#include "ui/message/message.h"
#include "ui/welcome/welcome.h"

void App::set_sizes(){
	int width;
	int height;
	term.get_sizes(width,height);
	screen = {0,0,width,height};

	int gap = 1;
	int x = 2;

	tabbar_rect = {x, 
		2, 
		screen.width - x*2, 
		2};

	help_rect = {x,
		screen.height - 5,
		screen.width - x*2,
		2};

	db_rect = {x, 
		tabbar_rect.y + tabbar_rect.height + gap, 
		screen.width - x*2, 
		 (help_rect.y + 2*gap) - (tabbar_rect.y + tabbar_rect.height + gap)};

	main_rects[0] = tabbar_rect;
	main_rects[1] = db_rect;
	help_bar.rect = help_rect;
}

void App::init(){
	recent_databases.load();
	recent_databases_paths = recent_databases.get();

	set_sizes();

	tabbar = std::make_unique<TabBar>(term, "", names);
	main_menus[0] = tabbar.get();

	welcome = std::make_unique<Welcome>(term, recent_databases_paths);
	main_menus[1] = welcome.get();
}

void App::render(){
	set_sizes();
	term.clear();

	if (main_menus.size() != main_rects.size()) return;
	if (names.size() != db_menus.size()) return;

	// main menus
	if (names.empty()){
		focused_menu = 1;
		main_menus[1] = welcome.get();
		main_rects[1] = {db_rect.x, tabbar_rect.y, db_rect.width, screen.height - tabbar_rect.y - help_rect.height}; 
	}
	else
		main_menus[1] = db_menus[tabbar->get_value()].get();

	for (int i = 0; i < main_menus.size(); i++){
		if (i == focused_menu && popups_stack.empty())
			main_menus[i]->render(main_rects[i], true); // focused
		else
			main_menus[i]->render(main_rects[i], false); // unfocused 
	}
	
	// popups
	if (popups_stack.size() > 0){
		Rect sizes = popups_stack[0]->preferred_size();
		Rect popup = Layout::centered_rect(screen,sizes.width,sizes.height);
		popups_stack[0]->render(popup, true);
	}

	// help bar
	if (names.empty())
		return;

	if (focused_menu == 0)
		help_bar.render({"o:open file", "x:close file"});

	if (focused_menu == 1)
		help_bar.render({"n:new creds", "f:filter", "e:edit", "d:delete", "g:sec pass", "q:exit"});

}

bool App::handle_input(char c) {
	if (!popups_stack.empty()){
		bool active = popups_stack[0]->handle_input(c);

		if (!active){
			main_menus[focused_menu]->pull_result(popups_stack[0]->get_str());
			popups_stack.erase(popups_stack.begin());
			pull_request();
		}

		return true;
	}

	bool handled = false;
	switch (c){
		case ESC:  // change focus
			focused_menu = 0 || names.empty();  // if names.empty dont toggle (focused = 1)
			return true;
			break;
		case ENTER:
			if (focused_menu == 0){
				focused_menu = 1;
				handled = true;
			}
			break;

		case 'q':
			return false;
			break;
	}

	if (!handled)
		main_menus[focused_menu]->handle_input(c);
	pull_request();
	return true;
}

void App::pull_request(){
	Ui_request request = main_menus[focused_menu]->pull_request();

	if (request.type == Ui_request::NONE) return;

	switch (request.type){
		case Ui_request::TEXT_MENU:
			popups_stack.push_back(std::make_unique<TextMenu>(term, request.title));
			break;

		case Ui_request::PATH_MENU:
			popups_stack.push_back(std::make_unique<PathMenu>(term, request.title, recent_databases_paths));
			break;

		case Ui_request::MESSAGE_MENU:
			popups_stack.push_back(std::make_unique<Message>(term, request.title, request.msg));
			break;

		case Ui_request::NUMBER_MENU:
			popups_stack.push_back(std::make_unique<NumberMenu>(term, request.title, request.min_value, request.max_value));
			break;

		case Ui_request::OPTIONS_MENU:
			popups_stack.push_back(std::make_unique<OptionMenu>(term, request.title, request.options));
			break;

		case Ui_request::OPEN_FILE:{
			bool opened = false;
			for (int i = 0; i < db_menus.size(); i++){
				opened = db_menus[i]->file() == request.db->db_file;
				if (opened){
					break;
				} 
			}
			if (!opened){
				db_menus.push_back(std::make_unique<DatabaseMenu>(term, request.db->db_file, *request.db, request.db->dump()));
				names.push_back(request.db->name);
			}
			recent_databases.add(request.db->db_file);
			recent_databases.update();
			recent_databases_paths = recent_databases.get();
			break;
		}

		case Ui_request::CLOSE_FILE:
			db_menus.erase(db_menus.begin() + tabbar->get_value());
			tabbar->close();
			break;

		default:
			return;
			break;
	}
}

void App::start(){
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

