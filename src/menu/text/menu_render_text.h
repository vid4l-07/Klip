#pragma once
#include <string>
#include "menu_render.h"
#include "rect.h"

class MenuRenderText: public MenuRender{
	std::string title;
	std::string current_str;
	public:
	void configure_render(const std::string& current_str_param) {current_str = current_str_param;}
	void draw();
	void render(Rect rect, bool focused) override;

	MenuRenderText(const std::string& title, Terminal& term_param): 
		MenuRender(title, term_param), title(title) {}
};
