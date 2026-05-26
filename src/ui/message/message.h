#pragma once
#include <string>
#include "term/term.h"
#include "ui/core/menu.h"
#include "ui/rect.h"

class Message: public Menu {
	void move_cursor(int rows, int columns);
	std::string title;
	std::string text;
	public:
	bool handle_input(char c) override { return false; }
	Rect preferred_size() override { return {0,0,30,4};}

	void render(Rect rect, bool important) override;
	Message(Terminal& term, std::string title, std::string text): title(title), text(text),
		Menu(title, term) {}
};

