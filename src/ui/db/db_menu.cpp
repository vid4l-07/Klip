#include <memory>
#include <string>
#include <vector>
#include "ui/db/db_menu.h"
#include "ui/rect.h"
#include "ui/ui_request.h"

#include "workflows/new_pass_workflow.h"
#include "workflows/filter_workflow.h"
#include "workflows/edit_workflow.h"
#include "workflows/remove_workflow.h"
#include "workflows/secure_pass_workflow.h"
#include "workflows/message_workflow.h"

bool DatabaseMenu::handle_input(char c) {
	switch (c) {
		case '\n':
			if (secondary_selection >= 0){
				if (secondary_selection == 0) term.copy(options[current_selection].user);
				else term.copy(options[current_selection].pass);

				std::string prefix;
				if (secondary_selection == 0) prefix = "user";
				else if (secondary_selection == 1) prefix = "pass";
				else prefix = "other";

				active_workflow = std::make_unique<MessageWorkflow>(options[current_selection].site + " " + prefix + " copied to clipboard");
				active_workflow->start();
			}
			secondary_selection = -(secondary_selection != -1);
			break;
		case KEY_DOWN:
		case 'j':
			select(true);
			break;
		case KEY_UP:
		case 'k':
			select(false);
			break;
		case 'n':
			new_pass();
			break;
		case 'f':
			filter();
			break;
		case 'e':
			edit();
			break;
		case 'd':
			remove();
			break;
		case 'g':
			sec_pass();
			break;
	}
	return true;
}

void DatabaseMenu::select(bool direction){
	int* selection = nullptr;
	int size;
	if (secondary_selection < 0) {
		size = options.size();
		selection = &current_selection; 
	}
	else {
		size = 2;
		selection = &secondary_selection; 
	}

	if (direction){
		if (*selection < size - 1){
			(*selection) ++;
		}
	} else {
		if (*selection > 0){
			(*selection) --;
		}
	}
}

void DatabaseMenu::new_pass(){
	active_workflow = std::make_unique<NewPassWorkflow>(db, options);
	active_workflow->start();
}

void DatabaseMenu::filter(){
	active_workflow = std::make_unique<FilterWorkflow>(db,options);
	active_workflow->start();
	current_selection = 0;
}

void DatabaseMenu::edit(){
	active_workflow = std::make_unique<EditWorkflow>(db,options, current_selection);
	active_workflow->start();
}

void DatabaseMenu::remove(){
	active_workflow = std::make_unique<RemoveWorkflow>(db,options,current_selection);
	active_workflow->start();

	current_selection = 0;
}

void DatabaseMenu::sec_pass(){
	active_workflow = std::make_unique<SecurePassWorkflow>();
	active_workflow->start();
}

void DatabaseMenu::pull_result(const std::string result) {
	if (!active_workflow)
		return;

	active_workflow->pull_result(result);
	if (active_workflow->finished()) {
		active_workflow.reset();
	}
}

Ui_request DatabaseMenu::pull_request() {
	if (!active_workflow)
		return Ui_request{Ui_request::NONE};
	return active_workflow->pull_request();
}

int DatabaseMenu::get_value() {
	return current_selection;
}

void DatabaseMenu::render(Rect rect, bool focused) {
	menu_render.configure_render(current_selection, secondary_selection, focused);
	menu_render.render(rect, focused);
}
