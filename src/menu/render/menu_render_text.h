#include "menu_render_secondary.h"
#include <string>
#include <vector>

class MenuRenderText: public MenuRenderSecondary{
	public:
	void draw(std::string render_str);
	void render(const std::string& title, std::string render_str); 

	MenuRenderText(Terminal& term_param, int rows_size, int cols_size): 
	MenuRenderSecondary(term_param, rows_size, cols_size) {}
};
