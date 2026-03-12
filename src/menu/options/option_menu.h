#include "../core/menu.h"
#include "menu_render_options.h"
#include <string>

class OptionMenu: public Menu{
	private:
	std::vector<std::string> options;
	int current_selection;
	void select(bool direction);
	MenuRenderOptions menu_render;

	public:
	bool handle_input(char c) override;
	void render() override;
	int get_value() override;


	OptionMenu(Terminal& term_param, std::string title, std::vector<std::string>& options_param, int rows_size = 5, int cols_size = 20):
		Menu(title, term_param), menu_render(term_param, rows_size, cols_size), options(options_param), current_selection(0) {}
};
