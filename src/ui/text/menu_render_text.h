#pragma once
#include <string>
#include "ui/core/menu_render.h"
#include "ui/rect.h"

class MenuRenderText: public MenuRender{
	std::string title;
	std::string current_str;
	bool pass_mode;
	public:
	void configure_render(const std::string& current_str_param) {current_str = current_str_param;}
	void draw();
	void render(Rect rect, bool focused) override;

	MenuRenderText(const std::string& title, Terminal& term_param, bool pass_mode): 
		MenuRender(title, term_param), title(title), pass_mode(pass_mode) {}
};
