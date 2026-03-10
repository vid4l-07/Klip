#include <iostream>
#include <string>
#include "menu_render_text.h"

void MenuRenderText::draw(std::string current_str){
	int padding_top = (end_row - title_line)/2;
	int padding_left = 4;

	int text_size = col_size - padding_left * 2;
	int text_start_row = title_line + padding_top - 1;
	int text_start_col = start_col + padding_left;

	std::cout << "\033[?25h"; // show cursor
	while (current_str.size() >= text_size){
		current_str.erase(current_str.begin());
	}

	move_cursor(text_start_row, text_start_col);
	std::cout << current_str;

}

void MenuRenderText::render(const std::string& title, std::string render_str){
	draw_border();
	draw_title(title);
	draw(render_str);
}

