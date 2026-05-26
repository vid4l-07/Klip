#pragma once
#include "ui/ui_request.h"
#include <string>

class Workflow {
	public:
	virtual void start() = 0;
	virtual Ui_request pull_request() = 0;
	virtual void pull_result(const std::string result) = 0;
	virtual bool finished() = 0;
	virtual ~Workflow() = default;
};
