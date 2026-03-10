#pragma once
#include <string>
#include <vector>
#include "menu_render_primary.h"
#include "../../Creds.h"

class MenuRenderMain: public MenuRenderPrimary{
	public:
	int options_line = end_row - 3;
	void render(const std::string& title, const std::vector<Creds>& options, int selection);
	void draw(const std::vector<Creds>& options, int selection);
	void draw_data(std::vector<std::string> data);
	void draw_options();
	void draw_sec_pass(int chars);

	MenuRenderMain(Terminal& term_param, int rows_size, int cols_size): 
		MenuRenderPrimary(term_param, rows_size, cols_size) {}
};
