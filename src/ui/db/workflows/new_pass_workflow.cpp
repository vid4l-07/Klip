#include <string>
#include "new_pass_workflow.h"
#include "ui/ui_request.h"

bool NewPassWorkflow::finished(){
	return state == State::DONE;
}

void NewPassWorkflow::start(){
	state = State::SITE;
	pending_request = Ui_request();
	pending_request.type = Ui_request::TEXT_MENU;
	pending_request.title = "Site";
}

Ui_request NewPassWorkflow::pull_request(){
	auto tmp = pending_request;
	pending_request = Ui_request{.type = Ui_request::NONE};
	return tmp;
}

void NewPassWorkflow::pull_result(const std::string result){
	if (result.empty())
		state = DONE;

	switch (state){
		case SITE:
			site = result;
			state = USER;
			pending_request.type = Ui_request::TEXT_MENU;
			pending_request.title = "User";
			break;

		case USER:
			user = result;
			state = PASS;
			pending_request.type = Ui_request::TEXT_MENU;
			pending_request.title = "Pass";
			break;

		case PASS:
			pass = result;
			db.add(site,user,pass);
			db.update_db();
			org_options = db.dump();
			state = DONE;
			pending_request.type = Ui_request::NONE;
			break;

		default:
			return;
	}
}
