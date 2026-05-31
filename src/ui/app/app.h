#pragma once
#include <array>
#include <memory>
#include <string>
#include <vector>
#include "db/recent_databases.h"
#include "term/term.h"
#include "ui/db/db_menu.h"
#include "ui/core/menu.h"
#include "ui/help/help.h"
#include "ui/tabbar/tabbar.h"
#include "ui/welcome/welcome.h"

class App{
	protected:
	Terminal& term;
	Rect screen;
	private:
	std::vector<std::string> recent_databases_paths;
	RecentDatabases recent_databases;

	Help help_bar;

	Rect tabbar_rect;
	Rect help_rect;
	Rect db_rect;

	int focused_menu = 0;


	std::vector<std::unique_ptr<DatabaseMenu>> db_menus;
	std::vector<std::string> names;

	std::unique_ptr<TabBar> tabbar;
	std::unique_ptr<Welcome> welcome;

	std::array<MainMenu*, 2> main_menus; // [tabbar, selected_dbmenu or welcome screen]
	std::array<Rect, 2> main_rects; // [tabbar_rect, db_rect]

	std::vector<std::unique_ptr<Menu>> popups_stack;

	void set_sizes();
	void init();

	void pull_request();
	
	public:
	bool handle_input(char c);
	void render();
	void start();
	App(Terminal& term): term(term) {
		init();
	}
};
