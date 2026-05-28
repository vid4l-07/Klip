#include <memory>
#include "layout.h"
#include "app.h"

#include "Database.h"
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


void App::init(){
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

	tabbar = std::make_unique<TabBar>(term, "", names);

	main_menus[0] = tabbar.get();
	main_rects[0] = tabbar_rect;

	wellcome = std::make_unique<DatabaseMenu>(term, db.db_file, db, db.dump());

	main_menus[1] = wellcome.get();
	main_rects[1] = db_rect;

	help_bar.rect = help_rect;
}

void App::render(){
	term.clear();

	if (main_menus.size() != main_rects.size()) return;
	if (names.size() != db_menus.size()) return;

	// main menus
	if (names.empty())
		main_menus[1] = wellcome.get();
	else
		main_menus[1] = db_menus[tabbar->get_value()].get();

	for (int i = 0; i < main_menus.size(); i++){
		if (i == focused_menu && popups_stack.empty())
			main_menus[i]->render(main_rects[i], true); // focused
		else
			main_menus[i]->render(main_rects[i], false); // unfocused 
	}
	
	// help bar
	if (focused_menu == 0)
		help_bar.render({"o:open file", "x:close file"});

	if (focused_menu == 1)
		help_bar.render({"n:new creds", "f:filter", "e:edit", "d:delete", "g:sec pass", "q:exit"});
	
	// popups
	if (popups_stack.size() > 0){
		Rect sizes = popups_stack[0]->preferred_size();
		Rect popup = Layout::centered_rect(screen,sizes.width,sizes.height);
		popups_stack[0]->render(popup, true);
	}
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
			focused_menu = 0;
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
			popups_stack.push_back(std::make_unique<PathMenu>(term, request.title, request.options));
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
				if (opened) break;
			}
			if (!opened){
				db_menus.push_back(std::make_unique<DatabaseMenu>(term, request.db->db_file, *request.db, request.db->dump()));
				names.push_back(request.db->name);
			}
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

