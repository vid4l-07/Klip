#pragma once
#include <memory>
#include <string>
#include <vector>
#include "term/term.h"
#include "ui/db/db_menu.h"
#include "ui/core/menu.h"
#include "ui/help/help.h"
#include "ui/tabbar/tabbar.h"

class App{
	protected:
	Terminal& term;
	Rect screen;
	private:
	Help help_bar;

	int focused_menu = 0;

	std::vector<DatabaseMenu> db_menus;
	std::vector<std::string> names = {"ye", "nooo", "si claro"};

	std::unique_ptr<TabBar> tabbar;

	std::vector<std::unique_ptr<MainMenu>> main_menus;
	std::vector<Rect> main_rects;

	std::vector<std::unique_ptr<Menu>> popups_stack;

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
