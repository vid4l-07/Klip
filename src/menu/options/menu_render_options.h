#include "../core/menu_render_secondary.h"
#include <string>
#include <vector>

class Option{
	public:
	std::string str;
	bool selected;
	Option(std::string str_param): str(str_param), selected(false) {}
};

class MenuRenderOptions: public MenuRenderSecondary{
	public:
	void draw(const std::vector<std::string>& options, int selection);
	void render(const std::string& title, const std::vector<std::string>& options, int selection); 

	MenuRenderOptions(Terminal& term_param, int rows_size, int cols_size): MenuRenderSecondary(term_param, rows_size, cols_size) {}
};
