#pragma once

#include <ftxui/component/container.hpp>
#include <ftxui/component/checkbox.hpp>
//#include <ftxui/component/input.hpp>
#include "CustomInput.h"
#include "InputColumn.h"

#include "Task.h"

/**
 * \brief Sets up the "Priority" column
 */
class AllTask : public InputColumn {
public:
	void add_task(const std::shared_ptr<Task>& task) override;
};


