#pragma once
#include <vector>
#include <string>
#include "../text/text_menu.h"
#include "../text/menu_render_text.h"

class PathMenu: public TextMenu {
	private:
	MenuRenderText menu_render;
	int count = 0;
	const std::vector<std::string>& options;

	public:
	bool handle_input(char c) override;
	
	PathMenu(Terminal& term_param, std::string title, const std::vector<std::string>& options, int rows_size = 3, int cols_size = 30):
		TextMenu(term_param, title), menu_render(term_param, rows_size, cols_size), options(options) {}
};
