#include <fstream>
#include <filesystem>
#include <vector>

#include "RecentDatabases.h"

void RecentDatabases::load(){
	const char* homeDir = std::getenv("HOME");
	if (!homeDir) {
		throw "HOME not found";
    }
	file_path = (std::filesystem::path(homeDir) / ".config/klip/recents").string();

	std::fstream file(file_path);
	if (!file.is_open()){
		return;
	}

	std::string path;
	while (std::getline(file, path)){
		recents.push_back(path);
	}
	file.close();
}

void RecentDatabases::update(){
	std::ofstream file(file_path);
	std::string data;
	for (size_t i = 0; i < recents.size() && i < 4; i++) {
    data += recents[i] + "\n";
	}
	file << data;
	file.close();
}

void RecentDatabases::add(const std::string& path){
	if (path.empty()) return;

	for (int i; i < recents.size(); i++){
		if (recents[i] == path){
			recents.erase(recents.begin() + i);
			break;
		}
	}
	recents.insert(recents.begin(), path);
}

const std::vector<std::string>& RecentDatabases::get() const{
	return recents;
}
