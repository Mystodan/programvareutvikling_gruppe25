#pragma once
#include "CheckboxColumn.h"

class DeleteTask : public CheckboxColumn {
public:
	void add_task(const std::shared_ptr<Task>& task) override;	
};
