#include <iostream>
#include <string>
#include "ui/rect.h"
#include "message.h"

void Message::move_cursor(int rows, int columns){
	std::cout << "\033[" << rows << ";" << columns << "H";
}

void Message::render(Rect rect, bool important){
	text = "  " + text + "  ";
	int x = rect.x;
	int y = rect.y;
	int rows = y + rect.height/2;
	int columns = x + rect.width/2;

	size_t size = text.size();
	int start_row;
	
	if (!title.empty()){
		move_cursor(rows - 3, columns - title.size()/2);
		for (int i = 0; i < size; i++)
			std::cout << " " ;
		move_cursor(rows - 2, columns - title.size()/2);
		std::cout << title;
	}

	move_cursor(rows - 1, columns - text.size()/2);
	for (int i = 0; i < size; i++)
		std::cout << " " ;

	move_cursor(rows + 1, columns - text.size()/2);
	for (int i = 0; i < size; i++)
		std::cout << " " ;

	move_cursor(rows, columns - text.size()/2);
	std::cout << text;
}
