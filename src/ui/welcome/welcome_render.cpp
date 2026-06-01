#include <iostream>
#include <string>
#include <vector>
#include "welcome_render.h"
#include "ui/config.h"
#include "ui/rect.h"

void WelcomeRender::draw(){
	int bar_size = 40;

	std::string banner1 = "\033[34m┌─┐\033[0m";
	std::string banner2 = "\033[34m│\033[33m│\033[34m│\033[33m│\033[0m";
	std::string banner3 = "\033[34m│\033[33m│\033[34m│\033[33m│\033[0m";
	std::string banner4 = " \033[33m└─┘\033[0m";
	std::string name = "\033[34mKlip\033[0m";

	std::vector<std::string> banner = {banner1, banner2, banner3, banner4};
	int y = rows - 3 - banner.size();


	auto draw_line = [&](int row){
		for (int i = 0; i <= bar_size; i++){
			move_cursor(row, columns - bar_size/2 + i);
			std::cout << "─";
		}
	};

	// banner
	for (int i = 0; i < banner.size(); i++){
		move_cursor(y, columns - 2);
		std::cout << banner[i];
		y++;
	}

	move_cursor(y, columns - 2);
	std::cout << name;
	y++;

	// recents
	if (!options.empty()){
		draw_line(y);
		y+=2;

		std::string title = "Recent files:";
		move_cursor(y, columns - title.size()/2);
		std::cout << title;
		y += 2;

		for (int i = 0; i < options.size(); i++){
			move_cursor(y, columns - options[i].size()/2);
			if (i == selection) {
				std::cout << "\033[" << colors::SELECTED_COLOR_FG << ";" << colors::SELECTED_COLOR_BG << "m" << options[i]; 
				std::cout << "\033[0m";
			}
			else {
				std::cout << options[i];
				std::cout << "\033[0m";
			}
			y++;
		}
	}

	// github
	std::string github_intro = "You can contribute on github";
	std::string github = "https://github.com/vid4l-07/Klip";

	y++;
	draw_line(y);

	y++;
	move_cursor(y, columns - github_intro.size()/2);
	std::cout << github_intro;

	y++;
	move_cursor(y, columns - github.size()/2);
	std::cout << github;

	y++;
	draw_line(y);

	// help 

	y+=2;
	std::string help = "o: open new file";
	move_cursor(y, columns - help.size()/2);
	std::cout << help;

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
