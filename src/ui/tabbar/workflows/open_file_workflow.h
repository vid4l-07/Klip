#pragma once
#include "ui/core/workflow.h"
#include "db/recent_databases.h"

class OpenFileWorkflow: public Workflow {
	enum State{  // possible states of the workflow
		FILE,
		PASS,
		FINISH,
		DONE
	};
	public:

	State state = State::DONE;

	RecentDatabases recent_db;
	
	std::string file;
	std::string pass;

	Ui_request pending_request;

	void start() override;
	Ui_request pull_request() override;
	void pull_result(const std::string result) override;
	bool finished() override;

	OpenFileWorkflow() {}
};

