#pragma once
#include <string>
#include "menu.h"
#include "term/term.h"
#include "ui/ui_request.h"

class MainMenu: public Menu {
	public:
	virtual void pull_result(const std::string result) = 0;
	virtual Ui_request pull_request() = 0;
	MainMenu(Terminal& term, std::string title):
		Menu(title,term) {}
};
