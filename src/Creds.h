#pragma once
#include <string>
#include <vector>

struct Creds{
	std::string sitio;
	std::string user;
	std::string pass;

	std::vector<std::string> dump() const;
	bool in(const std::vector<Creds>& vector) const;
	bool operator==(const Creds& otro) const;
};

