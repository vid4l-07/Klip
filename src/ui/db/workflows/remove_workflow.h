#pragma once
#include "ui/core/workflow.h"
#include "db/database.h"
#include "Creds.h"
#include <string>

class RemoveWorkflow: public Workflow {
	enum State{  // possible states of the workflow
		CONFIRM,
		DONE
	};
	public:

	State state = State::DONE;
	
	Database& db;
	std::vector<Creds>& org_options;
	int current_selection;
	std::string selection;

	Ui_request pending_request;

	void start() override;
	Ui_request pull_request() override;
	void pull_result(const std::string result) override;
	bool finished() override;

	RemoveWorkflow(Database& db, std::vector<Creds>& org_options, int current_selection): 
		db(db), org_options(org_options), current_selection(current_selection) {}
};
