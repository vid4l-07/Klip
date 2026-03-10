#include <iostream>
#include "menu_render_number.h"

void MenuRenderNumber::draw(int value){
	int padding_top = rows * 0.2;
	move_cursor(rows, columns);
	std::cout << value;
}

void MenuRenderNumber::render(const std::string& title, int value){
	draw_border();
	draw_title(title);
	draw(value);
}
