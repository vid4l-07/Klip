#pragma once
#include <vector>
#include <string>
#include "ui/text/text_menu.h"
#include "ui/text/menu_render_text.h"

class PathMenu: public TextMenu {
	private:
	MenuRenderText menu_render;
	int count = 0;
	std::vector<std::string> options;

	public:
	bool handle_input(char c) override;
	
	PathMenu(Terminal& term_param, std::string title, std::vector<std::string> options):
		TextMenu(term_param, title, false), menu_render(title, term_param, false), options(options) {}
};
