#pragma once
#include "rect.h"
#include <iostream>
#include <string>

class Message {
	static void move_cursor(int rows, int columns);
	public:
	static void render(Rect rect, const std::string& title, const std::string& text);
};

void Message::move_cursor(int rows, int columns){
	std::cout << "\033[" << rows << ";" << columns << "H";
}

void Message::render(Rect rect, const std::string& title, const std::string& text){
	int rows = rect.height - rect.height/2;
	int columns = rect.width - rect.width/2;
	size_t size = text.size();
	int start_row;
	if (!title.empty()){
		move_cursor(rows - 3, columns);
		for (int i = 0; i < size; i++)
			std::cout << " " ;
		move_cursor(rows - 2, columns - title.size()/2);
		std::cout << title;
	}

	move_cursor(rows - 1, columns);
	for (int i = 0; i < size; i++)
		std::cout << " " ;

	move_cursor(rows + 1, columns);
	for (int i = 0; i < size; i++)
		std::cout << " " ;

	move_cursor(rows, columns - text.size()/2);
	std::cout << text;
	std::cin.get();
}
