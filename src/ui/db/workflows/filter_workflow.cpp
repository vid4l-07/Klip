#include "filter_workflow.h"


bool FilterWorkflow::finished(){
	return state == State::DONE;
}

void FilterWorkflow::start(){
	state = State::SITE;
	pending_request = Ui_request();
	pending_request.type = Ui_request::TEXT;
	pending_request.title = "Site";
}

Ui_request FilterWorkflow::pull_request(){
	auto tmp = pending_request;
	pending_request = Ui_request{.type = Ui_request::NONE};
	return tmp;
}

void FilterWorkflow::pull_result(const std::string result){
	switch (state){
		case SITE:
			site = result;
			org_options = db.find(site);
			state = DONE;
			pending_request.type = Ui_request::NONE;
			break;
		default:
			return;
	}
}
