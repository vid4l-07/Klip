#include <stdexcept>
#include <random>
#include <string>
#include <sodium.h>
#include <vector>

#include "Security.h"

Security::Security(){
	if (sodium_init() < 0) {
		throw std::runtime_error("Libsodium could not initialize");
	}
}

bool Security::derive_key(const std::string& password, const unsigned char* raw_salt, unsigned char* key) {
    return crypto_pwhash(
        key,
        crypto_secretbox_KEYBYTES,
        password.c_str(),
        password.size(),
        raw_salt,
        crypto_pwhash_OPSLIMIT_INTERACTIVE,
        crypto_pwhash_MEMLIMIT_INTERACTIVE,
        crypto_pwhash_ALG_DEFAULT) == 0;
}

bool Security::encrypt(const std::string& plaintext, const std::string& password, std::vector<unsigned char>& out) {
    unsigned char salt[crypto_pwhash_SALTBYTES];
    unsigned char key[crypto_secretbox_KEYBYTES];
    unsigned char nonce[crypto_secretbox_NONCEBYTES];

    randombytes_buf(salt, sizeof salt);
    randombytes_buf(nonce, sizeof nonce);

    if (!derive_key(password, salt, key)) {
        return false;
    }

    std::vector<unsigned char> ciphertext(plaintext.size() + crypto_secretbox_MACBYTES);

    if (crypto_secretbox_easy(
        ciphertext.data(),
        (const unsigned char*)plaintext.data(),
        plaintext.size(),
        nonce,
        key) < 0) {
		sodium_memzero(key, sizeof key);
		return false;
	}

    // save: salt + nonce + ciphertext
    out.clear();
    out.insert(out.end(), salt, salt + sizeof salt);
    out.insert(out.end(), nonce, nonce + sizeof nonce);
    out.insert(out.end(), ciphertext.begin(), ciphertext.end());

    sodium_memzero(key, sizeof key);
    return true;
}



bool Security::decrypt(const std::vector<unsigned char>& input, const std::string& password, std::string& plaintext) {
    if (input.size() < crypto_pwhash_SALTBYTES + crypto_secretbox_NONCEBYTES) {
        return false;
    }

    const unsigned char* salt = input.data();
    const unsigned char* nonce = input.data() + crypto_pwhash_SALTBYTES;
    const unsigned char* ciphertext = input.data() + crypto_pwhash_SALTBYTES + crypto_secretbox_NONCEBYTES;

    size_t ciphertext_len = input.size() - crypto_pwhash_SALTBYTES - crypto_secretbox_NONCEBYTES;

    unsigned char key[crypto_secretbox_KEYBYTES];

    if (!derive_key(password, salt, key)) {
        return false;
    }

    std::vector<unsigned char> decrypted(ciphertext_len);

    if (crypto_secretbox_open_easy(
        decrypted.data(),
        ciphertext,
        ciphertext_len,
        nonce,
        key) != 0) {	// invalid pass or corrupted db
        sodium_memzero(key, sizeof key);
        return false;
    }

    plaintext.assign((char*)decrypted.data(), decrypted.size());

    sodium_memzero(key, sizeof key);
    return true;
}

std::string Security::genPass(int longitud){
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
