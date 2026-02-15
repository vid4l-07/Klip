#ifndef AUTH_H
#define AUTH_H
#include <string>

class Auth{
	std::string password;
	std::string pass_file;

	public:
	Auth(const std::string& file);
	bool validate_pass();
	void new_pass(const std::string& pass);
	bool log_in(const std::string& trypass);
};
#endif
