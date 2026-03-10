#pragma once
#include "menu.h"
#include <string>
#include "render/menu_render_number.h"

class NumberMenu: public Menu{
	private:
	int value;
	int min_value;
	int max_value;
	MenuRenderNumber menu_render;

	public:
	bool handle_input(char c) override;
	void render() override;
	int get_value() override;


	NumberMenu(Terminal& term_param, std::string title, int min_value = 0, int max_value = 100, int rows_size = 6, int cols_size = 20): 
		Menu(title, term_param), menu_render(term_param, rows_size, cols_size), value(5), min_value(min_value), max_value(max_value) {}
};
