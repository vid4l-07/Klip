#include <iostream>
#include <vector>
#include <string>
#include "menu_render_main.h"
#include "../../Security.h"

void MenuRenderMain::draw(const std::vector<Creds>& options, int selection){
	int padding_top = 2;
	int padding_col = 3;
	int padding_row = 2;

	int number_options = options.size();

	int options_start_col = start_col + padding_col;
	int options_start_row = title_line + padding_top;
	int max_options = (((end_row - title_line)) - padding_top * 2) / padding_row + 1;

	int start = (selection / max_options) * max_options;

	move_cursor(options_start_row, options_start_col);
	for (int i = 0; i < max_options && (start + i) < options.size(); i++) {
		int option_index = start + i;
		move_cursor(options_start_row, options_start_col);

		if (option_index == selection) {
			int size = options[option_index].sitio.size() + padding_col;

			std::cout << "\033[7m" << options[option_index].sitio;
			for (int j = options_start_col; j <= columns - size; j++) {
				std::cout << " ";
			}
			std::cout << "\033[0m";

			draw_data(options[option_index].dump());
		} 
		else {
			std::cout << options[option_index].sitio;
		}
		options_start_row += padding_row;
	}
}

void MenuRenderMain::draw_data(std::vector<std::string> data){
	int padding_top = 2;
	int padding_col = 3;
	int padding_row = 2;
	for (int i = title_line; i <= end_row; i++){
		move_cursor(i, columns);
		if (i == title_line){
			std::cout << "┬";
		} else if (i == end_row) {
			std::cout << "┴";
		} else{
			std::cout << "│";
		}
	}

	int options_start_col = columns;
	int options_start_row = title_line + padding_top;

	options_start_col += padding_col;
	move_cursor(options_start_row, options_start_col);

	for (int i = 0; i < data.size(); i++){
		move_cursor(options_start_row, options_start_col);
		std::cout << data[i];
		options_start_row += padding_row;
	}
}

void MenuRenderMain::draw_options(){
	end_row = options_line;
    std::vector<std::string> guide = {"n:new creds", "f:filter", "e:edit", "d:delete", "g:sec pass", "q:exit"};

    int total_width = col_size - 4;
    int total_text_length = 0;
    for (auto &opt : guide) total_text_length += opt.size();

    int space_count = guide.size() + 1;
    int space_size = (total_width - total_text_length) / space_count;

    std::vector<std::string> line1, line2;
    if (space_size < 1) {
        int half = guide.size() / 2;
        line1.assign(guide.begin(), guide.begin() + half);
        line2.assign(guide.begin() + half, guide.end());
    } else {
        line1 = guide; 
    }

    auto draw_line = [&](const std::vector<std::string>& options, int y) {
        int text_length = 0;
        for (auto &opt : options) text_length += opt.size();
        int spaces = options.size() + 1;
        int space_sz = (total_width - text_length) / spaces;

        int pos = start_col + 2 + space_sz;
        for (auto &opt : options) {
            move_cursor(y, pos);
            std::cout << opt;
            pos += opt.size() + space_sz;
        }
    };

    move_cursor(options_line, start_col + 2);
    for (int i = start_col; i < end_col - 2; i++) std::cout << "─";

    draw_line(line1, options_line + 1);

    if (!line2.empty()) draw_line(line2, options_line + 2);

    std::cout << "\n";
}

void MenuRenderMain::render(const std::string& title, const std::vector<Creds>& options, int selection){
	draw_border();
	draw_title(title);
	draw_options();
	draw(options, selection);
}

void MenuRenderMain::draw_sec_pass(int chars){
	term.clear();
	std::string pass = Security::generarContrasena(chars);
	std::string title = "Secure pass:";
	move_cursor(rows-2, columns - title.size() / 2);
	std::cout <<title;
	move_cursor(rows, columns - pass.size() / 2);
	std::cout << pass;
	std::cin.get();
}
