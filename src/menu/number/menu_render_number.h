#pragma once
#include <string>
#include <vector>
#include "../core/menu_render_secondary.h"

class MenuRenderNumber: public MenuRenderSecondary{
	public:
	void draw(int value);
	void render(const std::string& title, int value);

	MenuRenderNumber(Terminal& term_param, int rows_size, int cols_size):
	MenuRenderSecondary(term_param, rows_size, cols_size) {}
};
