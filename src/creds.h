#pragma once
#include <string>
#include <vector>

struct Creds{
	std::string site;
	std::string user;
	std::string pass;
	bool operator==(const Creds& otro) const {
	return site == otro.site && user == otro.user && pass == otro.pass;
}
};
