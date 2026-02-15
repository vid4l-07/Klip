#ifndef DATABASE_H
#define DATABASE_H
#include "Creds.h"
#include <string>
#include <array>
#include <vector>

class Database{
	std::string db_file;
	std::vector<Creds> data_vector;
	std::vector<std::string> split(const std::string& data, char separador);

	public:
	Database(const std::string& file);

	const std::vector<Creds>& dump() const { return data_vector; }
	std::vector<Creds> find(const std::string& sitio);
	void load();
	void add(const std::string& site, const std::string& user, const std::string& pass);
	void update_db();
	void edit(int indice, const std::string& new_user, const std::string& new_pass);
	void remove(int indice);
	void clear();
};

#endif
