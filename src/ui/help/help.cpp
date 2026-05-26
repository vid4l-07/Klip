#include <string>
#include <vector>
#include <iostream>
#include "help.h"
#include "ui/rect.h"
#include "ui/colors.h"

void Help::move_cursor(int rows, int columns){
	std::cout << "\033[" << rows << ";" << columns << "H";
}

void Help::render(const std::vector<std::string>& guide) {
	int start_col = rect.x;
	int start_row = rect.y;
	int end_col = rect.x + rect.width;
	int end_row = rect.y + rect.height;
	int row_size = rect.height;
	int col_size = rect.width;
	int rows = start_row + row_size/2;
	int columns = start_col + col_size/2;

	int options_line = end_row;

    int total_width = col_size - 4;
    int total_text_length = 0;
    for (auto &opt : guide) total_text_length += opt.size();

    int space_count = guide.size() + 1;
    int space_size = (total_width - total_text_length) / space_count;

    std::vector<std::string> line1, line2;
    if (space_size < 2) {
        int half = guide.size() / 2;
        line1.assign(guide.begin(), guide.begin() + half);
        line2.assign(guide.begin() + half, guide.end());
    } else {
        line1 = guide; 
    }

    auto draw_line = [&](const std::vector<std::string>& options, int y) {
        int text_length = 0;
        for (auto &opt : options)
			text_length += opt.size();
        int spaces = options.size() + 1;
        int space_sz = (total_width - text_length) / spaces;

        int pos = start_col + 2 + space_sz;
        for (auto &opt : options) {
            move_cursor(y, pos);
            std::cout << "\033[" << colors::GUIDE_COLOR << "m" << opt << "\033[0m"; // Print colored option
            pos += opt.size() + space_sz;
        }
    };

    draw_line(line1, options_line + 1);

    if (!line2.empty()) draw_line(line2, options_line + 2);

    std::cout << "\n";
}
