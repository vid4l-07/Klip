#pragma once
#include <string>
#include <vector>
#include "../term/term.h"

class Menu{
	protected:
	Terminal& term;

	public:
	std::string title;
	virtual bool handle_input(char c) = 0;
	virtual void render() = 0;
	virtual int get_value() { return 0; };
	virtual std::string get_str() { return ""; };
	void end();
	void start();

	Menu(std::string title_param, Terminal& term_param): title(title_param), 
	term(term_param){}
};
