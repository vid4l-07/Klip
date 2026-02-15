#ifndef UI_H
#define UI_H
#include "Database.h"
#include "Auth.h"
#include <string>

class UI{
	static const std::string banner0;
	static const std::string banner1;
	Database db;
	Auth auth;
	void cls();
	int elegir();

	public:
	UI(Database& database, Auth& auth);
	void mainmenu();
	void ver_contrasenas_menu();
	void ver_filtradas(const std::string& filtro);
	
};

#endif
