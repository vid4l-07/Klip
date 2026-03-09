#pragma once
#include <vector>
#include <string>
#include "../../term/term.h"

class MenuRender {
	protected:
	Terminal& term;
	int rows;
	int columns;
	int title_row;
	int title_line;
	int row_size;
	int col_size;
	int start_col;
	int start_row;
	int end_col;
	int end_row;

	std::string border;
	void gen_border();
	void draw_border();
	void get_sizes(int rows_size, int cols_size);
	virtual void draw_title(const std::string& title) = 0;

	public:
	void move_cursor(int rows, int columns);

	MenuRender(Terminal& term_param, int rows_size, int cols_size): term(term_param) {
		term.get_center(rows, columns);
		get_sizes(rows_size, cols_size);
		gen_border();
	}
};
