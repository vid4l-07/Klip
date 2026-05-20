#pragma once
#include <string>
#include <vector>
#include "../core/menu_render.h"
#include "../../Creds.h"

class MenuRenderDatabase: public MenuRender{
	private:
	void draw(const std::vector<Creds>& options, int selection, int sec_selection);
	void draw_data(const std::string& user, const std::string& pass, int selection);
	void draw_options();
	public:
	int options_line = end_row - 3;
	void render(const std::string& title, const std::vector<Creds>& options, int selection, int sec_selection, int border_color = 0);
	void draw_sec_pass(int chars);
	void msg(const std::string& msg);

	MenuRenderDatabase(Terminal& term_param, int rows_size, int cols_size): 
		MenuRender(term_param, rows_size, cols_size) {}
};
