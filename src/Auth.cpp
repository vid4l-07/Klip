#include <fstream>
#include <string>
#include "Auth.h"
#include "Security.h"

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
	archivo_pass << Security::hash(pass);
}

bool Auth::log_in(const std::string& trypass){
	return Security::hash(trypass) == password;
}

std::string Auth::get_hash(){
	return password;
}
