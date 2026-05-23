#pragma once
#include <memory>
#include <string>
#include <vector>
#include "main_menu_render.h"
#include "term.h"
#include "../db/db_menu.h"
#include "menu.h"

class MainMenu{
	protected:
	Terminal& term;
	MainMenuRender menu_render;
	Rect screen;
	private:
	int focused_menu = 0;

	std::vector<DatabaseMenu> db_menus;
	std::vector<std::unique_ptr<Menu>> main_menus;
	std::vector<std::unique_ptr<Menu>> popups_stack;

	std::vector<std::string> names = {"ye", "nooo", "si claro"};
	std::vector<std::string> names2 = {"hola", "adios", "que tal"};

	bool open_file();

	void init();
	
	public:
	bool handle_input(char c);
	void render();
	void start();
	MainMenu(Terminal& term): term(term) {
		init();
	}
};
