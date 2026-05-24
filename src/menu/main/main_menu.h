#pragma once
#include <memory>
#include <string>
#include <vector>
#include "term.h"
#include "../db/db_menu.h"
#include "menu.h"
#include "help/help.h"

class MainMenu{
	protected:
	Terminal& term;
	Rect screen;
	private:
	Help help_bar;

	int focused_menu = 0;

	std::vector<DatabaseMenu> db_menus;
	std::vector<std::string> names = {"ye", "nooo", "si claro"};

	std::vector<std::unique_ptr<Menu>> main_menus;
	std::vector<Rect> main_rects;

	std::vector<std::unique_ptr<Menu>> popups_stack;

	void init();
	
	public:
	bool handle_input(char c);
	void render();
	void start();
	MainMenu(Terminal& term): term(term) {
		init();
	}
};
