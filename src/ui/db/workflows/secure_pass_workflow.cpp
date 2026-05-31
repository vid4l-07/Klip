#include "secure_pass_workflow.h"
#include "security/security.h"
#include <string>

bool SecurePassWorkflow::finished(){
	return state == State::DONE;
}

void SecurePassWorkflow::start(){
	state = State::SIZE;
	pending_request = Ui_request();
	pending_request.type = Ui_request::NUMBER_MENU;
	pending_request.title = "Number of chars";
}

Ui_request SecurePassWorkflow::pull_request(){
	auto tmp = pending_request;
	pending_request = Ui_request{.type = Ui_request::NONE};
	return tmp;
}

void SecurePassWorkflow::pull_result(const std::string result){
	if (result.empty())
		state = DONE;

	switch (state){
		case SIZE:
			size = std::stoi(result);
			state = RENDER;
			pending_request.type = Ui_request::MESSAGE_MENU;
			pending_request.title = "Secure pass:";
			pending_request.msg = Security::genPass(size);
			break;

		case RENDER:
			state = DONE;
			pending_request.type = Ui_request::NONE;
			break;
		default:
			return;
	}
}
