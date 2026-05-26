#pragma once
#include <vector>
#include <string>
#include "ui/rect.h"

class Help {
	private:
	void move_cursor(int rows, int columns);
	public: 
	Rect rect;
	void render(const std::vector<std::string>& guide);
};
