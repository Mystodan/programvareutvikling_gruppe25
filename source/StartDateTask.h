#pragma once

#include "InputColumn.h"

/**
* \Forward declaration of task
*/
class Task;

/**
* \brief StartDateTask includes: filling, adding & clearing StartDateTask data
*/
class StartDateTask : public InputColumn {
public:
    void add_task(const std::shared_ptr<Task>& task) override;
};
