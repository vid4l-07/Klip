#pragma once
#include <string>
#include "../core/menu.h"
#include "menu_render_db.h"
#include "../../Creds.h"
#include "../../Database.h"
#include "rect.h"

class DatabaseMenu: public Menu{
	private:
	std::vector<Creds> options;
	int current_selection = 0;
	int secondary_selection = -1;
	void select(bool direction);
	MenuRenderDatabase menu_render;
	Database& db;

	public:
	bool handle_input(char c) override;
	void render(Rect rect, int border_color) override;
	int get_value() override;

	void new_pass();
	void filter();
	void edit();
	void remove();
	void sec_pass();
	Rect preferred_size() override { return {0,0,0,0};}


	DatabaseMenu(Terminal& term_param, Database& db, std::string title, const std::vector<Creds>& options_param):
	Menu(title, term_param), menu_render(title, term_param, options), db(db), options(options_param){}
};
