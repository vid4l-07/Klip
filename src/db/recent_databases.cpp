#include <fstream>
#include <filesystem>
#include <vector>

#include "recent_databases.h"

void RecentDatabases::load(){
	recents.clear();
	const char* homeDir = std::getenv("HOME");
	if (!homeDir) {
		throw "HOME not found";
    }

	std::filesystem::path configDir = std::filesystem::path(homeDir) / ".config" / "klip";
	std::filesystem::path filePath = configDir / "recents";

	file_path = (std::filesystem::path(filePath)).string();

	std::filesystem::create_directories(configDir);

	std::fstream file(file_path);
	if (!file.is_open()){
		return;
	}

	std::string path;
	while (std::getline(file, path)){
		if (std::filesystem::exists(path)) {
            recents.push_back(path);
        }
	}
	file.close();
	update();
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

	for (int i = 0; i < recents.size(); i++){
		if (recents[i] == path){
			recents.erase(recents.begin() + i);
			break;
		}
	}
	recents.insert(recents.begin(), path);
	if (recents.size() > 4){
		recents.pop_back();
	}
}

std::vector<std::string> RecentDatabases::get() const{
	return recents;
}
