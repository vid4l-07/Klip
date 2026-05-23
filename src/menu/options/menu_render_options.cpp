#include <iostream>
#include <vector>
#include <string>
#include "menu_render_options.h"
#include "rect.h"

void MenuRenderOptions::draw(){
	if (options.empty()) return;

	bool center = false;

	int padding_top = 0;
	int space = 4;  // space between otpions
	int padding_left = space;

	int number_options = options.size();

	int total_width = 0;
	for (const std::string& i : options){
		total_width += i.size() + space;
	}

	int options_start_col;
	if (center)
		options_start_col = columns - total_width / 2;
	else
		options_start_col = start_col + padding_left;
	int options_start_row = rows;

	for (int i = 0; i < options.size(); i++){
		space += options[i].size();

		move_cursor(options_start_row, options_start_col);
		if (i == selection){
			std::cout << "\033[7m" << options[i] << "\033[0m"; // selected format
		} else {
			std::cout << options[i];
		}
		options_start_col += space;
		space -= options[i].size();
	}
}

void MenuRenderOptions::render(Rect rect, int border_color) {
	get_sizes(rect.x,rect.y,rect.width,rect.height);
	draw_border(border_color);
	draw_title(title);
	draw();
}
