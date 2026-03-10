#pragma once
#include <string>

class Auth{
	std::string password;
	std::string pass_file;

	public:
	Auth(const std::string& file): pass_file(file){}
	bool validate_pass();
	void new_pass(const std::string& pass);
	bool log_in(const std::string& trypass);
};
