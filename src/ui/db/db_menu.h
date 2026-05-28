#pragma once
#include <memory>
#include <string>
#include "ui/core/main_menu.h"
#include "menu_render_db.h"
#include "Creds.h"
#include "Database.h"
#include "ui/rect.h"
#include "ui/core/workflow.h"
#include "ui/ui_request.h"

class DatabaseMenu: public MainMenu{
	private:
	std::vector<Creds> options;
	int current_selection = 0;
	int secondary_selection = -1;
	void select(bool direction);
	MenuRenderDatabase menu_render;
	Database db;

	std::unique_ptr<Workflow> active_workflow;

	public:

	bool handle_input(char c) override;
	void render(Rect rect, bool focused) override;
	int get_value() override;

	void new_pass();
	void filter();
	void edit();
	void remove();
	void sec_pass();
	Rect preferred_size() override { return {0,0,20,30};}

	void pull_result(const std::string result) override;
	Ui_request pull_request() override;

	DatabaseMenu(Terminal& term, std::string title, Database db, const std::vector<Creds>& options_param):
		MainMenu(term, title), db(db), options(options_param), menu_render(title, term, options){}
};
