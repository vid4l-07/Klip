#include "message_workflow.h"

bool MessageWorkflow::finished(){
	return state == State::DONE;
}

void MessageWorkflow::start(){
	state = State::RENDER;
	pending_request = Ui_request();
	pending_request.type = Ui_request::MESSAGE_MENU;
	pending_request.msg = text;
}

Ui_request MessageWorkflow::pull_request(){
	auto tmp = pending_request;
	pending_request = Ui_request{.type = Ui_request::NONE};
	return tmp;
}

void MessageWorkflow::pull_result(const std::string result){
	if (result.empty())
		state = DONE;

	switch (state){
		case RENDER:
			state = DONE;
			pending_request.type = Ui_request::NONE;
			break;
		default:
			return;
	}
}
