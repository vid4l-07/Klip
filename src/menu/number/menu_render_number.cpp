#include <iostream>
#include "menu_render_number.h"

void MenuRenderNumber::draw(){
	move_cursor(rows, columns);
	std::cout << value;
}

void MenuRenderNumber::render(Rect rect, int border_color){
	get_sizes(rect.x,rect.y,rect.width,rect.height);
	draw_border(border_color);
	draw_title(title);
	draw();
}
