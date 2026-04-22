#pragma once
#include <termios.h>
#include <string>

enum Key{
	KEY_MIN = 32,
	KEY_UP = 65,
	KEY_DOWN = 66,
	KEY_RIGHT = 67,
	KEY_LEFT = 68,
	KEY_BACKSPACE = 127,
	ENTER = 10,
	ESC = 27
};

class Terminal { 
	private:
	termios oldt;

	public:
	Terminal();
	~Terminal();

	bool key_pressed();
	char read_char();
	void clear();
	void get_center(int& rows, int& columns);
	void copy(const std::string& input);
	void change_screen();
};
