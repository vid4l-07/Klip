#include <csignal>
#include <iostream>
#include <string>

#include <filesystem>

#include "Database.h"
#include "RecentDatabases.h"
#include "menu/main/main_menu.h"
#include "menu/path/path_menu.h"
#include "term/term.h"
#include "menu/options/option_menu.h"

int main(int argc, char* argv[]){
	Terminal term;

	std::string pass;
	std::cout << "Password: " << std::flush;
	std::cin >> pass;
	std::cin.get();

	term.change_screen();

	RecentDatabases recent_db;

	std::string db_file;
	if (argc > 1){
		db_file = argv[1];
	} else {
		PathMenu db_file_menu(term, "Database file", recent_db.get());
		db_file_menu.start();
		db_file = db_file_menu.get_str();
	}

	std::filesystem::path file(db_file);
	std::filesystem::path ruta = file.parent_path();

	if (ruta.empty()){
		ruta = "";
	}
	if (!std::filesystem::exists(ruta) || !std::filesystem::is_directory(ruta)){
		return 1;
	}

	recent_db.add(db_file);
	recent_db.update();

	signal(SIGINT, SIG_IGN);  // Ignore Ctrl+C

	Database db = Database(db_file);
	if (!db.load(pass)){
		std::cout << "wrong pass";
		std::cin.get();
		return 1;
	}

	MainMenu main_menu(term, db, db_file, db.dump());
	main_menu.start();
}
