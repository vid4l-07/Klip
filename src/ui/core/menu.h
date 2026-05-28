#pragma once
#include <string>
#include "term/term.h"
#include "ui/rect.h"

class Menu{
	protected:
	Terminal& term;
	
	public:
	std::string title;
	virtual bool handle_input(char c) = 0;
	virtual void render(Rect rect, bool focused) = 0;
	virtual Rect preferred_size() = 0;
	virtual int get_value() { return 0; };
	virtual std::string get_str() { return ""; };

	void end();
	void start();

    virtual ~Menu() = default;
	Menu(const std::string& title, Terminal& term): title(title), term(term){}
};
