#pragma once
#include <memory>
#include <string>
#include "welcome_render.h"

#include "ui/core/main_menu.h"
#include "ui/rect.h"
#include "ui/core/workflow.h"
#include "ui/ui_request.h"

class Welcome: public MainMenu{
	private:
	WelcomeRender menu_render;
	int current_selection = 0;
	std::string title;

	void select(bool direction);
	std::vector<std::string>& options;

	std::unique_ptr<Workflow> active_workflow;

	void open_file();
	void open_recent();

	public:

	bool handle_input(char c) override;
	void render(Rect rect, bool focused) override;

	Rect preferred_size() override { return {0,0,20,30};}

	void pull_result(const std::string result) override;
	Ui_request pull_request() override;

	Welcome(Terminal& term, std::vector<std::string>& recent_files, std::string title = ""): title(title),
		MainMenu(term, title), options(recent_files), menu_render(term, title, recent_files) {}
};
