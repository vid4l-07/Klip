#include <iostream>
#include "menu_render_number.h"
#include "ui/config.h"

void MenuRenderNumber::draw(){
	move_cursor(rows, columns);
	std::cout << value;
}

void MenuRenderNumber::render(Rect rect, bool focused){
	get_sizes(rect.x,rect.y,rect.width,rect.height);
	if (focused)
		draw_border(FOCUSED_BORDER_COLOR);
	else
		draw_border(UNFOCUSED_BORDER_COLOR);
	draw_title(title);
	draw();
}
