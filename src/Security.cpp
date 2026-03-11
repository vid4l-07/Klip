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

std::string toHex(const std::string& input) {
    static const char* hex = "0123456789abcdef";
    std::string output;
    output.reserve(input.size() * 2);

    for (unsigned char c : input) {
        output.push_back(hex[c >> 4]);
        output.push_back(hex[c & 0x0F]);
    }

    return output;
}

std::string fromHex(const std::string& input) {
    std::string output;
    output.reserve(input.size() / 2);

    for (size_t i = 0; i < input.size(); i += 2) {
        std::string byte = input.substr(i, 2);
        char chr = (char) strtol(byte.c_str(), nullptr, 16);
        output.push_back(chr);
    }

    return output;
}

std::string Security::encriptar(const std::string& texto, const std::string& hash) {
	std::mt19937 rng = generarPRNG(hash);
    std::string resultado = texto;

    for (size_t i = 0; i < texto.size(); i++) {
        unsigned char key = rng() % 126;
        resultado[i] = texto[i] ^ key;
    }

    return toHex(resultado);
}

std::string Security::desencriptar(const std::string& texto, const std::string& hash) {
	std::string binario = fromHex(texto);

    std::mt19937 rng = generarPRNG(hash);
    std::string resultado = binario;

    for (size_t i = 0; i < binario.size(); i++) {
        unsigned char key = rng() % 126;
        resultado[i] = binario[i] ^ key;
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
