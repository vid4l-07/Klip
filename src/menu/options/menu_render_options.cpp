#include <iostream>
#include <vector>
#include <string>
#include "menu_render_options.h"

void MenuRenderOptions::draw(const std::vector<std::string>& options, int selection){
	if (options.empty()) return;

	int padding_top = 0;
	int padding_col = 3;
	int padding_row = 5;
	int space = 3;
	int number_options = options.size();

	int total_width = 0;
	for (const std::string& i : options){
		total_width += i.size() + space;
	}

	int options_start_col = columns - total_width / 2;
	int options_start_row = rows;
	options_start_col += padding_col;

	move_cursor(options_start_row, options_start_col);
	for (int i = 0; i < options.size(); i++){
		space += options[i].size();

		move_cursor(options_start_row, options_start_col - (options[i].size() / 2));
		if (i == selection){
			std::cout << "\033[7m" << options[i] << "\033[0m";
		} else {
			std::cout << options[i];
		}
		options_start_col += space;
		space -= options[i].size();
	}
}

void MenuRenderOptions::render(const std::string& title, const std::vector<std::string>& options, int selection){
	draw_border();
	draw_title(title);
	draw(options, selection);
}

