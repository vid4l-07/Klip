#pragma once
#include "ui/core/workflow.h"
#include <string>

class CloseFileWorkflow: public Workflow {
	enum State{  // possible states of the workflow
		CONFIRM,
		FINISH,
		DONE
	};
	public:

	State state = State::DONE;

	Ui_request pending_request;
	std::string file;
	std::string selected;

	void start() override;
	Ui_request pull_request() override;
	void pull_result(const std::string result) override;
	bool finished() override;

	CloseFileWorkflow(const std::string& file): file(file) {}
};

