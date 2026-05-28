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

	int total_width = 0;
	for (const std::string& i : options){
		total_width += i.size() + space;
	}

	int options_start_col = start_col + padding_left;
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

void TabBarRender::render(Rect rect, bool focused) {
	get_sizes(rect.x,rect.y,rect.width,rect.height);
	if (focused)
		draw_border(FOCUSED_BORDER_COLOR);
	else
		draw_border(UNFOCUSED_BORDER_COLOR);
	draw_title(title);
	draw();
}
