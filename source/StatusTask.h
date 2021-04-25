#pragma once

#include "InputColumn.h"

/**
* Forward declaration of task
*/
class Task;

/**
* \brief StatusTask includes: filling, adding & clearing status data
*/
class StatusTask : public InputColumn {
public:
    void add_task(const std::shared_ptr<Task>& task) override;
};
