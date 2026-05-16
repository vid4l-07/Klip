#pragma once
#include <string>

struct Security{
	public:
	std::string salt;
	std::string nonce;

	std::string encrypt(const std::string& texto, const std::string& hash) const;
	std::string decrypt(const std::string& texto, const std::string& hash) const;
	static std::string hash(const std::string& texto);
	static std::string genPass(int longitud);
};

