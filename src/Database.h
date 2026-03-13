#pragma once
#include <string>
#include <array>
#include <vector>
#include "Creds.h"

class Database{
	std::string db_file;
	std::string hash;
	std::vector<Creds> data_vector;
	std::vector<std::string> split(const std::string& data, char separador);

	public:
	Database(const std::string& file, const std::string& hash): db_file(file), hash(hash) { load(); }

	const std::vector<Creds>& dump() const { return data_vector; }
	std::vector<Creds> find(const std::string& site);
	void load();
	void add(const std::string& site, const std::string& user, const std::string& pass);
	void update_db();
	void edit(const Creds& cred, const std::string& new_user, const std::string& new_pass);
	void remove(const Creds& cred);
	void clear();
};

