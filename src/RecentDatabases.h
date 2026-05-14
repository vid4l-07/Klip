#include <vector>
#include <string>

class RecentDatabases {
	private:
	std::vector<std::string> recents;
	std::string file_path;

	public:
	RecentDatabases() { load(); }
	
	void load();
	void update();

	void add(const std::string& path);

	const std::vector<std::string>& get() const;
};
