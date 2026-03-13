#include <string>
#include <vector>
#include <fstream>
#include "Database.h"
#include "Creds.h"
#include "Security.h"

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
			Security::desencriptar(content.at(0), hash),
			Security::desencriptar(content.at(1), hash), 
			Security::desencriptar(content.at(2), hash)
		};
		data_vector.push_back(c);
	}
}


std::vector<Creds> Database::find(const std::string& site){
	std::vector<Creds> result_vec;
	if (site == "") return data_vector;

	for (const Creds& i : data_vector){
		if (i.site == site) result_vec.push_back(i);
	}
	return result_vec;
}

void Database::add(const std::string& site, const std::string& user, const std::string& pass){
	if (site == "" || user == "" || pass == ""){
		return;
	}
	Creds c = {site, user, pass};
	data_vector.push_back(c);
}

void Database::update_db(){
	std::string data = "";
	for (const Creds& i:data_vector){
		data += Security::encriptar(i.site, hash) + ";" +
			Security::encriptar(i.user, hash) + ";" +
			Security::encriptar(i.pass, hash) + ";|";
	}

	std::ofstream db(db_file);
	db << data;
}


void Database::edit(int indice, const std::string& new_user, const std::string& new_pass){
	if (indice < 0 || indice >= data_vector.size()) return;

	if (new_user != "") data_vector[indice].user = new_user;
	if (new_pass != "") data_vector[indice].pass = new_pass;
}

void Database::remove(const std::string& site){
	int indice = 0;
	bool find = false;
	for (size_t i = 0; i < data_vector.size(); i++){
		if (data_vector[i].site == site){
			find = true;
			indice = i;
		} 
	}
	
	if (!find)return;
	else data_vector.erase(data_vector.begin() + indice);
}

void Database::clear(){
	data_vector.clear();
	std::ofstream db(db_file);
	db << "";
}
