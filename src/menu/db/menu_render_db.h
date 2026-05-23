#pragma once
#include <string>
#include <vector>
#include "menu_render.h"
#include "Creds.h"
#include "rect.h"

class MenuRenderDatabase: public MenuRender{
	private:
	void draw();
	void draw_data(const std::string& user, const std::string& pass, int selection);
	void draw_options();


	std::vector<Creds>& options;
	int selection = 0;
	int sec_selection = 0;

	public:
	void configure_render(int selection_param, int sec_selection_param, bool focused);

	void draw_sec_pass(int chars);
	void msg(const std::string& msg);
	void render(Rect rect, bool focused) override;

	MenuRenderDatabase(const std::string& title, Terminal& term, std::vector<Creds>& options): 
		MenuRender(title, term), options(options) {}
};
