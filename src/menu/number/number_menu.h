#pragma once
#include <string>
#include "../core/menu.h"
#include "menu_render_number.h"
#include "rect.h"

class NumberMenu: public Menu{
	private:
	int value;
	int min_value;
	int max_value;
	MenuRenderNumber menu_render;

	public:
	bool handle_input(char c) override;
	void render(Rect rect, int border_color = 0) override;
	int get_value() override;
	Rect preferred_size() override { return {0,0,14,6};}


	NumberMenu(Terminal& term, const std::string& title, int min_value = 0, int max_value = 100): 
		Menu(title, term), menu_render(title, term), value(5), min_value(min_value), max_value(max_value) {}
};
