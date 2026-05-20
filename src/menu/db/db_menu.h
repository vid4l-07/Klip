#pragma once
#include <string>
#include "../core/menu.h"
#include "menu_render_db.h"
#include "../../Creds.h"
#include "../../Database.h"

class DatabaseMenu: public Menu{
	private:
	std::vector<Creds> options;
	int current_selection;
	int secondary_selection;
	void select(bool direction);
	MenuRenderDatabase menu_render;
	Database& db;

	public:
	bool handle_input(char c) override;
	void render() override;
	int get_value() override;
	void new_pass();
	void filter();
	void edit();
	void remove();
	void sec_pass();


	DatabaseMenu(Terminal& term_param, Database& db, std::string title, const std::vector<Creds>& options_param, 
		int rows_size = 0, int cols_size = 0):
	Menu(title, term_param), menu_render(term_param, rows_size, cols_size), db(db), options(options_param),
	current_selection(0), secondary_selection(-1){}
};
