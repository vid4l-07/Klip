#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <iostream>
#include "term.h"

Terminal::Terminal() {
	termios newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	std::cout << "\033[?25l"; // hide cursor
}

Terminal::~Terminal() {
	clear();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	std::cout << "\033[?25h\033[H"; // show cursor and move to 0,0
	
}

bool Terminal::key_pressed(){
	timeval tv; 
	tv.tv_sec = 0;
	tv.tv_usec = 16000;  // delay
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	int ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

	if (ret == -1)
		return false;
	return FD_ISSET(STDIN_FILENO, &fds);
};

char Terminal::read_char(){
	return getchar();
}

void Terminal::clear(){
	std::cout << "\033[2J";
	std::cout << "\033[?25l"; // hide cursor
}

void Terminal::get_center(int& rows, int& columns) {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	rows = w.ws_row / 2;
	columns = w.ws_col / 2;
}

void Terminal::copy(const std::string& input) {
	static const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	std::string output;
	int val = 0, valb = -6;

	for (unsigned char c : input) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			output.push_back(base64_chars[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}

	if (valb > -6)
		output.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);

	while (output.size() % 4)
		output.push_back('=');

	std::cout << "\033]52;c;" << output << "\a";
}
