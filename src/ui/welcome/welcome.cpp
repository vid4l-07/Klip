#include <string>
#include <vector>
#include "ui/welcome/welcome.h"
#include "ui/rect.h"
#include "ui/ui_request.h"
#include "ui/tabbar/workflows/open_file_workflow.h"

bool Welcome::handle_input(char c) {
	switch (c) {
		case '\n':
			open_recent();
			break;
		case 'o':
			open_file();
			break;
		case KEY_DOWN:
		case 'j':
			select(true);
			break;
		case KEY_UP:
		case 'k':
			select(false);
			break;
	}
	return true;
}

void Welcome::select(bool direction){
	if (options.empty()) return;
	if (direction)
		current_selection = (current_selection + 1) % options.size();
	else
		current_selection = (current_selection - 1) % options.size(); 
}

void Welcome::open_file(){
	active_workflow = std::make_unique<OpenFileWorkflow>();
	active_workflow->start();
}

void Welcome::open_recent(){
	if (!(options.size() > 0))
		return;
	active_workflow = std::make_unique<OpenFileWorkflow>(options[current_selection]);
	active_workflow->start();
}

void Welcome::pull_result(const std::string result) {
	if (!active_workflow)
		return;

	active_workflow->pull_result(result);
	if (active_workflow->finished()) {
		active_workflow.reset();
	}
}

Ui_request Welcome::pull_request() {
	if (!active_workflow)
		return Ui_request{Ui_request::NONE};
	return active_workflow->pull_request();
}

void Welcome::render(Rect rect, bool focused) {
	menu_render.configure_render(current_selection, focused);
	menu_render.render(rect, focused);
}
