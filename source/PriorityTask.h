#pragma once
#include "CheckboxColumn.h"

class PriorityTask : public CheckboxColumn {
public:
	void add_task(const std::shared_ptr<Task>& task) override;	
};
