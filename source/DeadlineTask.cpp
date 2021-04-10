#include "DeadlineTask.h"
#include "TimeUtil.h"

void DeadlineTask::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	status_.entries.clear();
	for (const auto& task : tasks) {
		add_task(task);
	}
}

void DeadlineTask::add_task(const std::shared_ptr<Task>& task) {
	auto time = Utils::unixtime_to_string(task->get_end_time());

	status_.entries.emplace_back(time);
}

void DeadlineTask::clear() {
	status_.entries.clear();
}
