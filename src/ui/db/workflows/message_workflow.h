#pragma once
#include "ui/core/workflow.h"
#include <string>

class MessageWorkflow: public Workflow {
	enum State{  // possible states of the workflow
		RENDER,
		DONE
	};
	public:

	State state = State::DONE;
	
	std::string text;

	Ui_request pending_request;

	void start() override;
	Ui_request pull_request() override;
	void pull_result(const std::string result) override;
	bool finished() override;

	MessageWorkflow(std::string text): text(text) {}
};
