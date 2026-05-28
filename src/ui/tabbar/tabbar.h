#pragma once
#include <memory>
#include <string>

#include "ui/core/main_menu.h"
#include "tabbar_render.h"
#include "ui/rect.h"
#include "ui/core/workflow.h"

class TabBar: public MainMenu{
	private:
	std::vector<std::string>& options;
	int current_selection = 0;
	void select(bool direction);
	TabBarRender menu_render;

	std::unique_ptr<Workflow> active_workflow;

	void open_file();

	public:
	bool handle_input(char c) override;
	void render(Rect rect, bool focused) override;
	int get_value() override;
	std::string get_str() override;
	Rect preferred_size() override { return {0,0,20,30};}

	void pull_result(const std::string result) override;
	Ui_request pull_request() override;

	TabBar(Terminal& term_param, std::string title, std::vector<std::string>& options_param):
		MainMenu(term_param, title), menu_render(title, term_param, options), options(options_param) {}
};
