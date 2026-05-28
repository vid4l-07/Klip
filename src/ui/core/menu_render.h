#pragma once
#include <string>
#include "term/term.h"
#include "ui/rect.h"

class MenuRender {
	protected:
	Terminal& term;
	int rows;
	int columns;
	int row_size;
	int col_size;
	int start_col;
	int start_row;
	int end_col;
	int end_row;

	virtual void render(Rect rect, bool focused) = 0;
	void draw_border(int border_color = 0, bool center_line = false);
	void get_sizes(int x, int y, int width, int height);
	virtual void draw_title(const std::string& title);

	public:
	void move_cursor(int rows, int columns);

	MenuRender(const std::string& title, Terminal& term): term(term) {}
};
