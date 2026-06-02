#include "open_file_workflow.h"
#include "db/database.h"
#include "ui/ui_request.h"

bool OpenFileWorkflow::finished(){
	return state == State::DONE;
}

void OpenFileWorkflow::start(){
	if (file.empty()){
		state = FILE;
		pending_request = Ui_request();
		pending_request.type = Ui_request::PATH_MENU;
		pending_request.title = "File";
	} else {
		state = PASS;
		pending_request = Ui_request();
		pending_request.type = Ui_request::TEXT_MENU;
		pending_request.title = "Pass";
		pending_request.pass_mode = true;
	}
}

Ui_request OpenFileWorkflow::pull_request(){
	auto tmp = pending_request;
	pending_request = Ui_request{.type = Ui_request::NONE};
	return tmp;
}

void OpenFileWorkflow::pull_result(const std::string result){
	if (result.empty())
		state = DONE;

	switch (state){
		case FILE:
			file = result;
			state = PASS;
			pending_request.type = Ui_request::TEXT_MENU;
			pending_request.title = "Pass";
			pending_request.pass_mode = true;
			break;

		case PASS:{
			pass = result;
			Database db(file);
			if (db.load(pass)){
				pending_request.type = Ui_request::OPEN_FILE;
				pending_request.db = db;
				state = FINISH;
			}
			else {
				pending_request.type = Ui_request::MESSAGE_MENU;
				pending_request.msg = "Wrong pass or invalid file";
				state = FINISH;
			}
			break;
		}

		case FINISH:
				state = DONE;
				pending_request.type = Ui_request::NONE;

		default:
			return;
	}
}
