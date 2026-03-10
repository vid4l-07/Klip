#include <iostream>
#include "menu_render_secondary.h"

void MenuRenderSecondary::draw_title(const std::string& title){
	int center_col = columns - (title.size() / 2);
	move_cursor(start_row, start_col + 3);
	std::cout << " " << title << " ";
	std::cout << "\n";
}
