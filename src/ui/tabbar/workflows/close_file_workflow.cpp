#include "close_file_workflow.h"

bool CloseFileWorkflow::finished(){
	return state == State::DONE;
}

void CloseFileWorkflow::start(){
	state = State::CONFIRM;
	pending_request = Ui_request();
	pending_request.type = Ui_request::OPTIONS_MENU;
	pending_request.title = "Close " + file + "?";
	pending_request.options = {"no", "yes"};
}

Ui_request CloseFileWorkflow::pull_request(){
	auto tmp = pending_request;
	pending_request = Ui_request{.type = Ui_request::NONE};
	return tmp;
}

void CloseFileWorkflow::pull_result(const std::string result){
	if (result.empty())
		state = DONE;

	switch (state){
		case CONFIRM:
			selected = result;
			state = FINISH;

			if (selected == "yes")
				pending_request.type = Ui_request::CLOSE_FILE;
			break;

		case FINISH:
				state = DONE;
				pending_request.type = Ui_request::NONE;

		default:
			return;
	}
}
