#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "lib/json.hpp"

#include "Database.h"
#include "Creds.h"

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

bool Database::load(const std::string& pass_param){
	pass = pass_param;
	std::ifstream db(db_file, std::ios::binary);
	if (!db) return true; 
	data_vector.clear();

	std::vector<unsigned char> input;
	char c;
	while (db.get(c)) {
		input.push_back(static_cast<unsigned char>(c));
	}

	std::string decrypted_data;

	if (!security.decrypt(input, pass, decrypted_data))
		return false;

	nlohmann::json data = nlohmann::json::parse(decrypted_data);

	if (!data.contains("entries") || !data["entries"].is_array()) {
		return false;
	}
	for (const auto& i : data["entries"]){
		Creds c;
			c.site = i["site"];
			c.user = i["user"];
			c.pass = i["pass"];
		data_vector.push_back(c);
	}
	db.close();
	return true;
}

void Database::update_db(){
	std::ofstream db(db_file, std::ios::binary);

	nlohmann::json creds;
	creds["entries"] = nlohmann::json::array();
	
	for (const Creds& i : data_vector){
		creds["entries"].push_back({
			{"site", i.site},
			{"user", i.user},
			{"pass", i.pass}
		});
	}

	std::vector<unsigned char> encrypted_data;
	if (!security.encrypt(creds.dump(), pass, encrypted_data)){
		db.close();
		return; 
	}

	db.write((char*)encrypted_data.data(), encrypted_data.size());
	db.close();
}

std::vector<Creds> Database::find(const std::string& site){
	std::vector<Creds> result_vec;
	if (site.empty()) return data_vector;

	for (const Creds& i : data_vector){
		if (i.site.find(site) != std::string::npos) 
			result_vec.push_back(i);
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

void Database::edit(const Creds& cred, const std::string& new_user, const std::string& new_pass){
	if (new_user == "" && new_pass == "") return;

	int indice = 0;
	bool find = false;
	for (size_t i = 0; i < data_vector.size(); i++){
		if (data_vector[i] == cred){
			find = true;
			indice = i;
			break;
		} 
	}
	if (!find) return;
	else{
		if (new_user != "") data_vector[indice].user = new_user;
		if (new_pass != "") data_vector[indice].pass = new_pass;
	}
}

void Database::remove(const Creds& cred){
	int indice = 0;
	bool find = false;
	for (size_t i = 0; i < data_vector.size(); i++){
		if (data_vector[i] == cred){
			find = true;
			indice = i;
			break;
		} 
	}
	
	if (!find)return;
	else data_vector.erase(data_vector.begin() + indice);
}

void Database::clear(){
	data_vector.clear();
	std::ofstream db(db_file);
	db << "";
	db.close();
}
