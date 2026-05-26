#pragma once

#include <string>
#include <vector>
class Ui_request {
	public:
	enum Type {  // all possible menus
		NONE,
		TEXT,
		PATH,
		MESSAGE,
		NUMBER,
		OPTIONS,
	};
	
	Type type;

	// required parameters for each menu
	std::string title;
	std::string msg;
	int min_value = 0;
	int max_value = 100;
	std::vector<std::string> options;
};
