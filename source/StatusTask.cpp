#include "StatusTask.h"

#include "Category.h"
#include "EmptyCheckBox.h"
#include "Task.h"

void StatusTask::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	for (const auto& task : tasks) {
		add_task(task);
	}
}

void StatusTask::add_task(const std::shared_ptr<Task>& task) {
	status_.entries.push_back(std::to_wstring(task->get_status()));
}

void StatusTask::clear() {
	status_.entries.clear();
}
