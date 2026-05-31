#pragma once
#include <string>
#include <vector>

#include "creds.h"
#include "security/security.h"

class Database{
	std::string pass;

	Security security;

	std::vector<Creds> data_vector;

	public:
	std::string db_file;
	std::string name;

	const std::vector<Creds>& dump() const { return data_vector; }

	bool load(const std::string& pass_param);
	void update_db();

	std::vector<Creds> find(const std::string& site);
	void add(const std::string& site, const std::string& user, const std::string& pass);
	void edit(const Creds& cred, const std::string& new_user, const std::string& new_pass);
	void remove(const Creds& cred);
	void clear();

	Database(const std::string& file); // Database.cpp
};


