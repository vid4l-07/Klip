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
	KEY_TAB = 9,
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
	void hide_cursor();
	void get_center(int& rows, int& columns);
	void get_sizes(int& width, int& height);
	void copy(const std::string& input);
	void change_screen();
	void end();
};
