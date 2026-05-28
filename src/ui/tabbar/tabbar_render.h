#pragma once
#include "ui/core/menu_render.h"
#include "ui/rect.h"
#include <string>
#include <vector>

class TabBarRender: public MenuRender{
	private:
	std::vector<std::string>& options;
	std::string title;
	int selection = 0;
	public:
	void configure_render(int selection_param, bool focused);
	void draw();
	void render(Rect rect, bool focused) override;

	TabBarRender(const std::string& title, Terminal& term_param, std::vector<std::string>&options): 
		MenuRender(title, term_param), title(title), options(options) {}
};
