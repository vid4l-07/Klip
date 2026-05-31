#pragma once
#include <string>
#include <vector>
#include "ui/core/menu_render.h"
#include "ui/rect.h"

class WelcomeRender: public MenuRender{
	private:
	void draw();
	void draw_options();

	std::vector<std::string>& options;
	int selection = 0;

	public:
	void configure_render(int selection_param, bool focused);

	void render(Rect rect, bool focused) override;

	WelcomeRender(Terminal& term, std::string& title, std::vector<std::string>& options): 
		MenuRender(title, term), options(options) {}
};
