#include "StatusTask.h"

#include "Category.h"
#include "EmptyCheckBox.h"
#include "Task.h"

void StatusTask::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	for (const auto& task : tasks) {
		status_.entries.push_back(std::to_wstring(task->get_category().get_priority()));
	}
}
