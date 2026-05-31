#pragma once
#include <string>
#include <vector>

struct Security{
	bool derive_key(const std::string& password, const unsigned char* raw_salt, unsigned char* key);
	public:
	static std::string hash(const std::string& texto);

	Security();
	bool encrypt(const std::string& plaintext, const std::string& password, std::vector<unsigned char>& out);
	bool decrypt(const std::vector<unsigned char>& input, const std::string& password, std::string& plaintext);
	static std::string genPass(int longitud);
};

