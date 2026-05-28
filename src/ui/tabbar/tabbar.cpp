#include "tabbar.h"
#include <memory>
#include <string>
#include "ui/rect.h"
#include "workflows/open_file_workflow.h"

void TabBar::select(bool direction){
	if (direction){
		if (current_selection < int(options.size() - 1)){
			current_selection ++;
		}
	} else {
		if (current_selection > 0){
			current_selection --;
		}
	}
}

bool TabBar::handle_input(char c) {
	switch (c){
		case ENTER:
			return false;
			break;
		case 'l':
		case KEY_RIGHT:
			select(true);
			break;
		case 'h':
		case KEY_LEFT:
			select(false);
			break;

		case 'o':
			open_file();
			break;

	}
	return true;
}

void TabBar::open_file(){
	active_workflow = std::make_unique<OpenFileWorkflow>();
	active_workflow->start();
}

void TabBar::pull_result(const std::string result) {
	if (!active_workflow)
		return;

	active_workflow->pull_result(result);
	if (active_workflow->finished()) {
		active_workflow.reset();
	}
}

Ui_request TabBar::pull_request() {
	if (!active_workflow)
		return Ui_request{Ui_request::NONE};
	return active_workflow->pull_request();
}


int TabBar::get_value() {
	return current_selection;
}

std::string TabBar::get_str() {
	return options[current_selection];
}

void TabBar::render(Rect rect, bool focused) {
	menu_render.configure_render(current_selection, focused);
	menu_render.render(rect, focused);
}
