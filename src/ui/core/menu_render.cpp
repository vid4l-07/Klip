#include <string>
#include <iostream>
#include "menu_render.h"

void MenuRender::draw_title(const std::string& title){
	if (title.empty())
		return;
	move_cursor(start_row, start_col + 3);
	std::cout << " " << title << " ";
	std::cout << "\n";
}

void MenuRender::move_cursor(int rows, int columns){
	std::cout << "\033[" << rows << ";" << columns << "H";
}

void MenuRender::get_sizes(int x, int y, int width, int height){
	start_col = x;
	start_row = y;
	end_col = x + width;
	end_row = y + height;
	row_size = height;
	col_size = width;
	rows = start_row + (row_size + 1)/2;
	columns = start_col + (col_size + 1)/2;
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
				move_cursor(i, start_col+col_size/2);
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

