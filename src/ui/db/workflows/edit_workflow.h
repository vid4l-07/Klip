#pragma once
#include <vector>
#include <string>

#include "ui/core/workflow.h"
#include "db/database.h"
#include "db/creds.h"

class EditWorkflow: public Workflow {
	enum State{  // possible states of the workflow
		USER,
		PASS,
		DONE
	};
	public:

	State state = State::DONE;
	
	Database& db;
	std::vector<Creds>& org_options;
	std::string user;
	std::string pass;
	int current_selection;

	Ui_request pending_request;

	void start() override;
	Ui_request pull_request() override;
	void pull_result(const std::string result) override;
	bool finished() override;

	EditWorkflow(Database& db, std::vector<Creds>& org_options, int current_selection): 
		db(db), org_options(org_options), current_selection(current_selection) {}
};
