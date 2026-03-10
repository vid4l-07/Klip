#include <random>
#include "Security.h"
#include <string>
#include <functional>

std::string Security::hash(const std::string& texto) {
    std::hash<std::string> hasher;

    size_t h1 = hasher(texto);
    size_t h2 = hasher(texto + "aj92ja0]d@a34'");
    size_t h3 = hasher("kl';10#j1%90na" + texto);

    return std::to_string(h1) + std::to_string(h2) + std::to_string(h3);
}

static std::mt19937 generarPRNG(const std::string& hash) {
    std::seed_seq seed(hash.begin(), hash.end());
    return std::mt19937(seed);
}

std::string Security::encriptar(const std::string& texto, const std::string& hash) {
    std::mt19937 rng = generarPRNG(hash);
    std::string resultado = texto;

    for (size_t i = 0; i < texto.size(); i++) {

        unsigned char key = rng() % 256;
        resultado[i] = texto[i] ^ key;
    }
    return resultado;
}

std::string Security::desencriptar(const std::string& texto, const std::string& hash) {
    std::mt19937 rng = generarPRNG(hash);
    std::string resultado = texto;

    for (size_t i = 0; i < texto.size(); i++) {
        unsigned char key = rng() % 256;
        resultado[i] = texto[i] ^ key;
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
