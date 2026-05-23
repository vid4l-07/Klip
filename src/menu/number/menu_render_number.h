#pragma once
#include <string>
#include "menu_render.h"
#include "rect.h"

class MenuRenderNumber: public MenuRender{
	public:
	std::string title;
	void configure_render(int value_param) {value = value_param;}
	void draw();
	void render(Rect rect, bool focused) override;

	int value = 0;

	MenuRenderNumber(const std::string& title, Terminal& term_param):
	MenuRender(title, term_param), title(title) {}
};
