#include <string>
#include <iostream>
#include "menu_render.h"

void MenuRender::draw_title(const std::string& title){
	if (title.empty())
		return;
	int center_col = columns - (title.size() / 2);
	move_cursor(start_row, start_col + 3);
	std::cout << " " << title << " ";
	std::cout << "\n";
}

void MenuRender::move_cursor(int rows, int columns){
	std::cout << "\033[" << rows << ";" << columns << "H";
}

void MenuRender::get_sizes(int rows_size, int cols_size){
	if (rows_size < 2 || cols_size < 5){
		term.get_center(rows, columns);
		start_col = columns - columns + 2;
		start_row = rows - rows + 2;
		end_col = columns + columns - 2;
		end_row = rows + rows - 1;
		row_size = end_row - start_row;
		col_size = end_col - start_col;

	} else {
		row_size = rows_size;
		col_size = cols_size;

		start_col = columns - col_size / 2;
		start_row = rows - row_size / 2;
		end_col = columns + col_size / 2;
		end_row = rows + row_size / 2;
	}
}

void MenuRender::draw_border(int border_color, bool center_line){
	std::string horizontal = "─";
	std::string vertical = "│";
	// std::string top_left = "┌";
	// std::string top_right = "┐";
	// std::string bottom_left = "└";
	// std::string bottom_right = "┘";
	std::string top_right = "╮";
	std::string top_left = "╭";
	std::string bottom_left = "╰";
	std::string bottom_right = "╯";
	

	for (int i = start_row; i <= end_row; i++ ){
		for (int j = 0; j <= end_col; j++ ){
			if (i == start_row && j == start_col){
				move_cursor(i,j);
				std::cout << "\033[" << border_color << "m";
				std::cout << top_left;
			}

			else if (i == start_row && j == end_col){
				move_cursor(i,j);
				std::cout << "\033[" << border_color << "m";
				std::cout << top_right;
			}

			else if (i == end_row && j == start_col){
				move_cursor(i,j);
				std::cout << "\033[" << border_color << "m";
				std::cout << bottom_left;
			}

			else if (i == end_row && j == end_col){
				move_cursor(i,j);
				std::cout << "\033[" << border_color << "m";
				std::cout << bottom_right;
			}

			else if ((i == start_row || i == end_row) && j > start_col){
				move_cursor(i,j);
				std::cout << "\033[" << border_color << "m";
				std::cout << horizontal;
			}

			else if (j == start_col || j == end_col){
				move_cursor(i,j);
				std::cout << "\033[" << border_color << "m";
				std::cout << vertical;
			}

			else if (j < end_col && j > start_col){
				move_cursor(i,j);
				std::cout << " ";
			}
		}
		if (center_line){
			for (int i = start_row; i <= end_row; i++){
				move_cursor(i, columns);
				if (i == start_row){
					std::cout << "\033[" << border_color << "m";
					std::cout << "┬";
				} else if (i == end_row) {
					std::cout << "\033[" << border_color << "m";
					std::cout << "┴";
				} else{
					std::cout << "\033[" << border_color << "m";
					std::cout << "│";
				}
			}

		}

		std::cout << "\033[0m";
	}
}

