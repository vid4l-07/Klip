#pragma once

#include "Database.h"
#include <optional>
#include <string>
#include <vector>
class Ui_request {
	public:
	enum Type {  // all possible menus
		NONE,
		TEXT_MENU,
		PATH_MENU,
		MESSAGE_MENU,
		NUMBER_MENU,
		OPTIONS_MENU,
		OPEN_FILE,
		CLOSE_FILE,
	};
	
	Type type;

	// required parameters for each request
	// Menus
	std::string title;
	std::string msg;
	int min_value = 0;
	int max_value = 100;
	std::vector<std::string> options;

	// Files
	std::string file;
	std::optional<Database> db;
};
