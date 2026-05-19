#pragma once
#include <string>
#include "../core/menu_render.h"

class MenuRenderNumber: public MenuRender{
	public:
	void draw(int value);
	void render(const std::string& title, int value);

	MenuRenderNumber(Terminal& term_param, int rows_size, int cols_size):
	MenuRender(term_param, rows_size, cols_size) {}
};
