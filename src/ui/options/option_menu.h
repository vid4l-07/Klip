#pragma once
#include "ui/core/menu.h"
#include "menu_render_options.h"
#include "ui/rect.h"
#include <string>

class OptionMenu: public Menu{
	private:
	std::vector<std::string> options;
	int current_selection = 0;
	void select(bool direction);
	MenuRenderOptions menu_render;

	public:
	bool handle_input(char c) override;
	void render(Rect rect, bool focused) override;
	int get_value() override;
	Rect preferred_size() override { return {0,0,20,5};}


	OptionMenu(Terminal& term_param, std::string title, std::vector<std::string>& options_param):
		Menu(title, term_param), menu_render(title, term_param, options), options(options_param) {}
};
