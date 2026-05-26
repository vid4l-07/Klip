#pragma once
#include <string>
#include "ui/rect.h"

class Message {
	static void move_cursor(int rows, int columns);
	public:
	static void render(Rect rect, const std::string& title, const std::string& text);
};

