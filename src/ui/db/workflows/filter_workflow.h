#pragma once
#include "ui/core/workflow.h"
#include "db/database.h"
#include "Creds.h"
#include <vector>

class FilterWorkflow: public Workflow {
	enum State{  // possible states of the workflow
		SITE,
		DONE
	};
	public:

	State state = State::DONE;
	
	Database& db;
	std::vector<Creds>& org_options;
	std::string site;

	Ui_request pending_request;

	void start() override;
	Ui_request pull_request() override;
	void pull_result(const std::string result) override;
	bool finished() override;

	FilterWorkflow(Database& db, std::vector<Creds>& org_options): db(db), org_options(org_options) {}
};
