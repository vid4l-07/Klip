#include "Auth.h"
#include "Security.h"
#include <fstream>
#include <string>

Auth::Auth(const std::string& file): pass_file(file){}

bool Auth::validate_pass(){
	std::ifstream archivo(pass_file);
	if (!archivo.is_open()) return false;

	std::string tmp_pass;
	if (!std::getline(archivo, tmp_pass) || tmp_pass.empty())
		return false;

	password = tmp_pass;
	return true;
}

void Auth::new_pass(const std::string& pass){
	std::ofstream archivo_pass(pass_file);
	archivo_pass << Security::encriptar(pass);
}

bool Auth::log_in(const std::string& trypass){
	return Security::encriptar(trypass) == password;
}
