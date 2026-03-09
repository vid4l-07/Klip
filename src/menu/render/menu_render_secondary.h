#include "menu_render.h"

class MenuRenderSecondary: public MenuRender{
	public:
	void draw_title(const std::string& title) override;

	MenuRenderSecondary(Terminal& term_param, int rows_size, int cols_size): 
	MenuRender(term_param, rows_size, cols_size) {}
};
