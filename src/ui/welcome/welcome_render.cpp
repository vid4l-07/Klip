#include <iostream>
#include <string>
#include <vector>
#include "welcome_render.h"
#include "ui/config.h"
#include "ui/rect.h"

void WelcomeRender::draw(){

	if (options.empty()) return;

	std::string title = "Recent files:";
	move_cursor(rows, columns - title.size()/2);
	std::cout << title;

	for (int i = 0; i < options.size(); i++){
		move_cursor(rows + 2 + i, columns - options[i].size()/2);
		if (i == selection) {
			std::cout << "\033[" << colors::SELECTED_COLOR_FG << ";" << colors::SELECTED_COLOR_BG << "m" << options[i]; 
			std::cout << "\033[0m";
		}
		else {
			std::cout << options[i];
			std::cout << "\033[0m";
		}
	}
}

void WelcomeRender::configure_render(int selection_param, bool focused){
	if (focused){
		selection = selection_param;
	}
	else{
		selection = -1;
	}
}

void WelcomeRender::render(Rect rect, bool focused){
	get_sizes(rect.x,rect.y,rect.width,rect.height);
	bool center_border = options.size() > 0;
	if (focused)
		draw_border(FOCUSED_BORDER_COLOR, false);
	else
		draw_border(UNFOCUSED_BORDER_COLOR, false);
	draw();
}
