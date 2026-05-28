#include "remove_workflow.h"

bool RemoveWorkflow::finished(){
	return state == State::DONE;
}

void RemoveWorkflow::start(){
	state = State::CONFIRM;
	pending_request = Ui_request();
	pending_request.type = Ui_request::OPTIONS;
	pending_request.title = "Remove " + org_options[current_selection].site + "?";
	pending_request.options = {"no", "yes"};
}

Ui_request RemoveWorkflow::pull_request(){
	auto tmp = pending_request;
	pending_request = Ui_request{.type = Ui_request::NONE};
	return tmp;
}

void RemoveWorkflow::pull_result(const std::string result){
	if (result.empty())
		state = DONE;

	switch (state){
		case CONFIRM:
			selection = result;
			if (selection == "yes"){
				db.remove(org_options[current_selection]);
				db.update_db();
				org_options = db.dump();
			}

			state = DONE;
			pending_request.type = Ui_request::NONE;
			break;

		default:
			return;
	}
}
