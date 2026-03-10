#include <iostream>
#include <string>

#include <cstdlib>
#include <filesystem>
#include "Auth.h"
#include "Database.h"
#include "menu/main/main_menu.h"
#include "menu/text/text_menu.h"
#include "term/term.h"

int main(int argc, char* argv[]){
	const char* homeDir = std::getenv("HOME");
	if (!homeDir) {
        std::cerr << "No se pudo determinar HOME" << std::endl;
        return 1;
    }
    std::filesystem::path conf_dir = std::filesystem::path(homeDir) / ".config/klip";

	if (!std::filesystem::exists(conf_dir)) {
		std::filesystem::create_directory(conf_dir);
	}

	Auth auth = Auth((conf_dir / "password.txt").string());
	Terminal term;

	std::string pass;
	if (!auth.validate_pass()){
		std::cout << "Password not find, create one: " << std::flush;
		std::getline(std::cin, pass);
		auth.new_pass(pass);
		return 1;
	}

	bool log_in = false;
	for (int i = 0; i < 3; i++){
		std::cout << "Password: " << std::flush;
		std::getline(std::cin, pass);
		if (auth.log_in(pass)){
			log_in = true;
			break;
		}
		std::cout << "Contrasena incorrecta" << std::endl;
	}
	if (!log_in){
		return 1;
	}

	std::string db_file;
	if (argc > 1){
		db_file = argv[1];
	} else {
		TextMenu db_file_menu(term, "Database file");
		db_file_menu.start();
		db_file = db_file_menu.get_str();
	}

	Database db = Database(db_file, auth.get_hash());

	MainMenu main_menu(term, db, db_file, db.dump());
	main_menu.start();
}
