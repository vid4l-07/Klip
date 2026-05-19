#pragma once
#include <string>
#include "../core/menu_render.h"

class MenuRenderText: public MenuRender{
	public:
	void draw(std::string render_str);
	void render(const std::string& title, std::string render_str); 

	MenuRenderText(Terminal& term_param, int rows_size, int cols_size): 
	MenuRender(term_param, rows_size, cols_size) {}
};
