#pragma once
#include "Database.h"
#include "ui/core/workflow.h"
#include "ui/ui_request.h"
#include <string>

class NewPassWorkflow: public Workflow {
	enum State{  // possible states of the workflow
		SITE,
		USER,
		PASS,
		DONE
	};
	public:

	State state = State::DONE;
	
	Database& db;
	std::string site;
	std::string user;
	std::string pass;

	Ui_request pending_request;

	void start() override;
	Ui_request pull_request() override;
	void pull_result(const std::string result) override;
	bool finished() override;

	NewPassWorkflow(Database& db): db(db) {}
};
