#include <iostream>
#include <vector>
#include <string>
#include "menu_render_db.h"
#include "ui/colors.h"
#include "ui/rect.h"

void MenuRenderDatabase::draw(){
	int padding_top = 2;
	int padding_col = 3;
	int padding_row = 2;

	int number_options = options.size();

	int options_start_col = start_col + padding_col;
	int options_start_row = start_row + padding_top;
	int max_options = (((end_row - start_row)) - padding_top * 2) / padding_row + 1;

	int start = (selection / max_options) * max_options;

	move_cursor(options_start_row, options_start_col);
	for (int i = 0; i < max_options && (start + i) < options.size(); i++) {
		int option_index = start + i;
		move_cursor(options_start_row, options_start_col);

		if (option_index == selection) {
			int size = options[option_index].site.size() + padding_col;

			if (sec_selection < 0){
				std::cout << "\033[97;100m" << options[option_index].site; // colored primary selection
			} else {
				std::cout << options[option_index].site;
			}
			for (int j = options_start_col; j <= columns - size; j++) {  // print background line
				std::cout << " ";
			}
			std::cout << "\033[0m";

			draw_data(options[option_index].user, options[option_index].pass, sec_selection);
		} 
		else {
			std::cout << options[option_index].site;
		}
		options_start_row += padding_row;
	}
}

void MenuRenderDatabase::draw_data(const std::string& user, const std::string& pass, int selection){
	int padding_top = 2;
	int padding_col = 3;
	int padding_row = 2;

	int options_start_col = columns;
	int options_start_row = start_row + padding_top;

	options_start_col += padding_col;
	move_cursor(options_start_row, options_start_col);
	std::string prefix;
	std::string render_cred;

	for (int i = 0; i < 2; i++){
		if (i == 0) {
			prefix = "User: "; 
			render_cred = user;
		}
		else if (i == 1){
			prefix = "Pass: "; 
			render_cred = pass;
		}

		move_cursor(options_start_row, options_start_col);
		options_start_row += padding_row;
		if (i == selection) {
			int size = render_cred.size() + prefix.size() + padding_col;

			std::cout << "\033[97;100m" << prefix << render_cred;  // colored secondary selection
			for (int j = options_start_col; j <= end_col - size; j++) {  // print background line
				std::cout << " ";
			}
			std::cout << "\033[0m";

		} 
		else {
			std::cout << prefix << render_cred;
		}
	}
}

void MenuRenderDatabase::configure_render(int selection_param, int sec_selection_param, bool focused){
	if (focused){
		selection = selection_param;
		sec_selection = sec_selection_param;
	}
	else{
		selection = -1;
		sec_selection = -1;
	}
}

void MenuRenderDatabase::render(Rect rect, bool focused){
	get_sizes(rect.x,rect.y,rect.width,rect.height);
	bool center_border = options.size() > 0;
	if (focused)
		draw_border(FOCUSED_BORDER_COLOR, center_border);
	else
		draw_border(UNFOCUSED_BORDER_COLOR, center_border);
	draw_title(title);
	draw();
}
