#include "menu_render.h"
#include "rect.h"
#include <string>
#include <vector>

class Option{
	public:
	std::string str;
	bool selected;
	Option(std::string str_param): str(str_param), selected(false) {}
};

class MenuRenderOptions: public MenuRender{
	private:
	std::vector<std::string>& options;
	std::string title;
	int selection = 0;
	public:
	void configure_render(int selection_param, bool focused);
	void draw();
	void render(Rect rect, bool focused) override;

	MenuRenderOptions(const std::string& title, Terminal& term_param, std::vector<std::string>&options): 
		MenuRender(title, term_param), title(title), options(options) {}
};
