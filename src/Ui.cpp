#include "Ui.h"
#include "Database.h"
#include "Auth.h"
#include "Security.h"
#include <string>
#include <iostream>

const std::string UI::banner0 =
"┌──────────────────────────┐\n"
"│     PASSWORD MANAGER     │\n"
"├──────────────────────────┤\n"
"│ 1. Ver contraseñas       │\n"
"│ 2. Añadir nueva          │\n"
"│ 3. Generar contrasena    │\n"
"│ 99. Salir                │\n"
"└──────────────────────────┘\n";
const std::string UI::banner1 =
"┌──────────────────────────┐\n"
"│     PASSWORD MANAGER     │\n"
"├──────────────────────────┤\n"
"│ 1. Filtrar por sitio     │\n"
"│ 2. Editar                │\n"
"│ 3. Eliminar              │\n"
"│ 99. Volver               │\n"
"└──────────────────────────┘\n";

UI::UI(Database& database, Auth& auth_param): db(database), auth(auth_param){}

int UI::elegir(){
	while(true){
		std::string eleccion_str;
		std::getline(std::cin, eleccion_str);

		try {
			size_t pos;
			int eleccion = stoi(eleccion_str, &pos);

			if (pos == eleccion_str.length()) {
				return eleccion;
			}
		} catch (...) {
			std::cout << "Opcion incorrecta: " << std::flush;
		}
	}
}


void UI::cls(){
	std::cout << "\033[2J\033[1;1H";
}

void UI::ver_filtradas(const std::string& filtro){
	const auto& data_vector = db.dump();
	std::string format;

	for (size_t i = 0; i < data_vector.size(); ++i) {
		if (filtro.empty() || data_vector[i].sitio == filtro) {
			format += std::to_string(i) + ". " + data_vector[i].dump() + "\n";
		}
	}

	std::cout << format << std::endl;
}

void UI::ver_contrasenas_menu(){
	const auto& data_vector = db.dump();
	int eleccion = 0;
	std::string filtro = "";
	while (eleccion != 99){
		std::cout << banner1 << std::endl;
		ver_filtradas(filtro);
		std::cout << "> " << std::flush;
		eleccion = elegir();
		switch(eleccion){
			case 1: { // filtrar
						std::cout << "Sitio: " << std::flush;
						std::getline(std::cin, filtro);
						break;
					}
			case 2: { // editar
						std::cout << "Indice: " << std::flush;
						int indice = elegir();
						if (indice >= data_vector.size()){
							std::cout << "No existe" << std::endl;
							break;
						}
						std::string new_user;
						std::string new_pass;
						std::string continuar;
						std::cout << "Introduce nuevo usuario (vacio para no modificar): ";
						std::getline(std::cin, new_user);
						std::cout << "Introduce nueva contrasena (vacio para no modificar): ";
						std::getline(std::cin, new_pass);
						std::cout << "\nUsuario: " << new_user << "\nContrasena: " << new_pass;
						std::cout << "\nContinuar? (y/N): ";
						std::getline(std::cin, continuar);
						if (continuar == "y"){
							db.edit(indice, new_user, new_pass);
							db.update_db();
						}
						break;
					}
			case 3: { // eliminar
						std::cout << "Indice: " << std::flush;
						int indice = elegir();
						if (indice >= data_vector.size()){
							std::cout << "No existe" << std::endl;
							break;
						}
						std::cout << "Va a eliminar " << db.dump().at(indice).dump() << "\n";
						std::cout << "Continuar? (y/N)";
						std::string continuar;
						std::getline(std::cin, continuar);
						if (continuar == "y"){ 
							db.remove(indice);
							db.update_db();
						}
						break;
					}
		}
		cls();
	}
}

void UI::mainmenu(){
	int eleccion = 0;
	while (eleccion != 99) {
		std::cout << banner0 << std::endl;
		std::cout << "> " << std::flush;
		eleccion = elegir();

		switch (eleccion) {
			case 1: {  // ver contrasenas
				cls();
				ver_contrasenas_menu();
				break;
			}
			case 2:{  // nueva contrasena
				std::string site;
				std::string user;
				std::string pass;
				std::cout << "Sitio: " << std::flush;
				std::getline(std::cin, site);
				std::cout << "Usuario: " << std::flush;
				std::getline(std::cin, user);
				std::cout << "Contrasena: " << std::flush;
				std::getline(std::cin, pass);
				db.add(site, user, pass);
				db.update_db();
				cls();
				break;
			}
			case 3: {  // generar contrasena
				std::cout << "Longitud: " << std::flush;
				int longitud = elegir();
				std::cout << Security::generarContrasena(longitud) << std::endl;
				std::cout << ": " << std::flush;
				std::cin.get();
				cls();
				break;
			}
		}
	}
}
