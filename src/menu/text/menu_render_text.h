#pragma once
#include <string>
#include "../core/menu_render.h"
#include "rect.h"

class MenuRenderText: public MenuRender{
	std::string title;
	std::string current_str;
	public:
	void configure_render(const std::string& current_str_param) {current_str = current_str_param;}
	void draw();
	void render(Rect rect, int border_color = 0) override;

	MenuRenderText(const std::string& title, Terminal& term_param): 
		MenuRender(title, term_param), title(title) {}
};
