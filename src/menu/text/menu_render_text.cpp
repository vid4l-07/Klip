#include <iostream>
#include <string>
#include "menu_render_text.h"
#include "rect.h"

void MenuRenderText::draw(){
	int padding_top = (end_row - start_row)/2;
	int padding_left = 4;

	int text_size = col_size - padding_left * 2;
	int text_start_row = start_row + padding_top;
	int text_start_col = start_col + padding_left;

	std::cout << "\033[?25h"; // show cursor
	while (current_str.size() >= text_size){
		current_str.erase(current_str.begin());
	}

	move_cursor(text_start_row, text_start_col);
	std::cout << current_str;

}

void MenuRenderText::render(Rect rect, int border_color) {
	get_sizes(rect.x,rect.y,rect.width,rect.height);
	draw_border(border_color);
	draw_title(title);
	draw();
}

