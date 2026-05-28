#include <iostream>
#include <vector>
#include <string>
#include "tabbar_render.h"
#include "ui/colors.h"
#include "ui/rect.h"

void TabBarRender::configure_render(int selection_param, bool focused){
	if (focused)
		selection = selection_param;
	else
		selection = -1;
}

void TabBarRender::draw(){
	if (options.empty()) return;

	int padding_top = 0;
	int space = 4;  // space between otpions
	int padding_left = space;

	int number_options = options.size();

	int max_options = 0;
	int total_width = 0;

	for (const std::string& i : options){
		total_width += i.size() + space;
		if (total_width < col_size - padding_left*2)
			max_options += 1;
	}

	int options_start_col = start_col + padding_left;
	int options_start_row = rows;
	int start = (selection == - 1)? 0 : (selection / max_options) * max_options;

	for (int i = 0; i + start < options.size() && i < max_options; i++){
		int option_index = start + i;
		space += options[option_index].size();

		if (options.size() > max_options && option_index + max_options <= options.size()){
			move_cursor(options_start_row, end_col - padding_left);
			std::cout << ">";
		}

		move_cursor(options_start_row, options_start_col);
		if (option_index == selection){
			std::cout << "\033[7m" << options[option_index] << "\033[0m"; // selected format
		} else {
			std::cout << options[option_index];
		}
		options_start_col += space;
		space -= options[option_index].size();
	}
}

void TabBarRender::render(Rect rect, bool focused) {
	get_sizes(rect.x,rect.y,rect.width,rect.height);
	if (focused)
		draw_border(FOCUSED_BORDER_COLOR);
	else
		draw_border(UNFOCUSED_BORDER_COLOR);
	draw_title(title);
	draw();
}
