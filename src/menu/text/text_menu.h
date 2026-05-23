#pragma once
#include <string>
#include "../core/menu.h"
#include "menu_render_text.h"
#include "rect.h"

class TextMenu: public Menu{
	protected:
	std::string current_str;

	private:
	MenuRenderText menu_render;

	public:
	bool handle_input(char c) override;
	void render(Rect rect, int border_color) override;
	std::string get_str() override;
	Rect preferred_size() override { return {0,0,30,2};}


	TextMenu(Terminal& term_param, std::string title):
		Menu(title, term_param), menu_render(title, term_param) {}
};
