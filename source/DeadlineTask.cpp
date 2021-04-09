#include "DeadlineTask.h"

void DeadlineTask::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	status_.entries.clear();
	for (const auto& task : tasks) {
		status_.entries.push_back(std::to_wstring(task->get_end_time()));
	}
}
