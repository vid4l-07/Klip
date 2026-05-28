#pragma once
#include "ui/core/workflow.h"

class SecurePassWorkflow: public Workflow {
	enum State{  // possible states of the workflow
		SIZE,
		RENDER,
		DONE
	};
	public:

	State state = State::DONE;
	
	int size;

	Ui_request pending_request;

	void start() override;
	Ui_request pull_request() override;
	void pull_result(const std::string result) override;
	bool finished() override;

	SecurePassWorkflow() {}
};
