#pragma once
#include "ui/core/workflow.h"
#include <string>

class OpenFileWorkflow: public Workflow {
	enum State{  // possible states of the workflow
		FILE,
		PASS,
		FINISH,
		DONE
	};
	public:

	State state = State::DONE;

	std::string file;
	std::string pass;

	Ui_request pending_request;

	void start() override;
	Ui_request pull_request() override;
	void pull_result(const std::string result) override;
	bool finished() override;

	OpenFileWorkflow(std::string file = ""): file(file) {}
};

