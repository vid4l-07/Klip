#include "Security.h"
#include <random>
#include <string>

std::string Security::encriptar(const std::string& texto) {
	int clave = 3;
	std::string resultado = texto;

	for (int i = 0; i < texto.length(); i++) {
		resultado[i] = texto[i] + clave;
	}

	return resultado;
}

std::string Security::desencriptar(const std::string& texto) {
	int clave = 3;
	std::string resultado = texto;

	for (int i = 0; i < texto.length(); i++) {
		resultado[i] = texto[i] - clave;
	}

	return resultado;
}
std::string Security::generarContrasena(int longitud) {
	const std::string mayus = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const std::string minus = "abcdefghijklmnopqrstuvwxyz";
	const std::string numeros = "0123456789";
	const std::string simbolos = "!@#$%^&*()-_=+[]{}<>?";

	const std::string todos = mayus + minus + numeros + simbolos;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, todos.size() - 1);

	std::string contrasena;

	for (int i = 0; i < longitud; ++i) {
		contrasena += todos[dis(gen)];
	}

	return contrasena;
}
