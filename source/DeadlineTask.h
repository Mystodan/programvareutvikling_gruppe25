#pragma once

#include "InputColumn.h"
#include "Task.h"


/**
 * \brief Sets up the "Priority" column
 */
class DeadlineTask : public InputColumn {
public:
    void add_task(const std::shared_ptr<Task>& task) override;
};
