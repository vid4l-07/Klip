#include "menu.h"
#include "render/menu_render_text.h"
#include <string>

class TextMenu: public Menu{
	private:
	std::string current_str;
	MenuRenderText menu_render;

	public:
	bool handle_input(char c) override;
	void render() override;
	std::string get_str() override;


	TextMenu(Terminal& term_param, std::string title, int rows_size = 3, int cols_size = 30):
		Menu(title, term_param), menu_render(term_param, rows_size, cols_size) {}
};
