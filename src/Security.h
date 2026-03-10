#pragma once
#include <string>

struct Security{
	static std::string encriptar(const std::string& texto);
	static std::string desencriptar(const std::string& texto);
	static std::string hash(const std::string& texto);
	static std::string generarContrasena(int longitud);
};

