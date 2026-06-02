#include "edit_workflow.h"

bool EditWorkflow::finished(){
	return state == State::DONE;
}

void EditWorkflow::start(){
	state = State::USER;
	pending_request = Ui_request();
	pending_request.type = Ui_request::TEXT_MENU;
	pending_request.title = "User";
}

Ui_request EditWorkflow::pull_request(){
	auto tmp = pending_request;
	pending_request = Ui_request{.type = Ui_request::NONE};
	return tmp;
}

void EditWorkflow::pull_result(const std::string result){
	switch (state){
		case USER:
			user = result;
			state = PASS;
			pending_request.type = Ui_request::TEXT_MENU;
			pending_request.title = "Pass";
			break;

		case PASS:
			pass = result;
			db.edit(org_options[current_selection],user,pass);
			db.update_db();
			org_options = db.dump();
			state = DONE;
			pending_request.type = Ui_request::NONE;
			break;

		default:
			return;
	}
}
