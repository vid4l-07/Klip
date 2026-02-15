#include "Database.h"
#include "Creds.h"
#include "Security.h"
#include <string>
#include <vector>
#include <fstream>

Database::Database(const std::string& file): db_file(file) {}

std::vector<std::string> Database::split(const std::string& data, char separador){
	std::vector<std::string> result;
	std::string temp;
	for (char c : data){
		if (c == separador){
			result.push_back(temp);
			temp = "";
		}
		else temp += c;
	}
	return result;
}

void Database::load(){
	std::ifstream db(db_file);
	std::string file_content;
	data_vector.clear();
	if (!db) return; 

	while (getline(db, file_content, '|')){
		auto content = split(file_content, ';');
		Creds c = {
			Security::desencriptar(content.at(0)),
			Security::desencriptar(content.at(1)), 
			Security::desencriptar(content.at(2))
		};
		data_vector.push_back(c);
	}
}


std::vector<Creds> Database::find(const std::string& sitio){
	std::vector<Creds> result_vec;
	if (sitio == "") return data_vector;

	for (const Creds& i : data_vector){
		if (i.sitio == sitio) result_vec.push_back(i);
	}
	return result_vec;
}

void Database::add(const std::string& site, const std::string& user, const std::string& pass){
	Creds c = {site, user, pass};
	data_vector.push_back(c);
}

void Database::update_db(){
	std::string data = "";
	for (const Creds& i:data_vector){
		data += Security::encriptar(i.sitio) + ";" +
			Security::encriptar(i.user) + ";" +
			Security::encriptar(i.pass) + ";|";
	}

	std::ofstream db(db_file);
	db << data;
}


void Database::edit(int indice, const std::string& new_user, const std::string& new_pass){
	if (indice < 0 || indice >= data_vector.size()) return;

	if (new_user != "") data_vector.at(indice).user = new_user;
	if (new_pass != "") data_vector.at(indice).pass = new_pass;
}

void Database::remove(int indice){
	if (indice < 0 || indice >= data_vector.size()) return;

	data_vector.erase(data_vector.begin() + indice);
}

void Database::clear(){
	data_vector.clear();
	std::ofstream db(db_file);
	db << "";
}
