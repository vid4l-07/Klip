#include <iostream>
#include "menu_render_primary.h"

void MenuRenderPrimary::draw_title(const std::string& title){
	int center_col = columns - (title.size() / 2);
	move_cursor(title_line, start_col + 2);
	for (int i = start_col; i < end_col - 2; i++){
		std::cout << "─";
	}
	move_cursor(title_row, center_col);
	std::cout << title;
	std::cout << "\n";
}
