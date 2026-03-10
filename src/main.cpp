#include <iostream>
#include <string>

#include <cstdlib>
#include <filesystem>
#include "Auth.h"
#include "Database.h"
#include "menu/main/main_menu.h"
#include "term/term.h"

int main(){
	const char* homeDir = std::getenv("HOME");
	if (!homeDir) {
        std::cerr << "No se pudo determinar HOME" << std::endl;
        return 1;
    }
    std::filesystem::path conf_dir = std::filesystem::path(homeDir) / ".config/klip";

	if (!std::filesystem::exists(conf_dir)) {
		std::filesystem::create_directory(conf_dir);
	}

	std::string db_file = (conf_dir / "db.txt").string();
	Auth auth = Auth((conf_dir / "password.txt").string());
	Database db = Database(db_file);
	Terminal term;

	std::string pass;
	if (!auth.validate_pass()){
		std::cout << "No se ha encontrado ninguna contrasena, ingrese una: " << std::flush;
		std::getline(std::cin, pass);
		auth.new_pass(pass);
		db.clear();
		return 1;
	}

	bool log_in = false;
	for (int i = 0; i < 3; i++){
		std::cout << "Ingrese la contrasena: " << std::flush;
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

	MainMenu main_menu(term, db, db_file, db.dump());
	main_menu.start();
}
