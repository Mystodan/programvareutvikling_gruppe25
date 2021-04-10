#include "StartDateTask.h"

#include "Task.h"
#include "TimeUtil.h"

void StartDateTask::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	status_.entries.clear();
	for (const auto& task : tasks) {
		add_task(task);
	}
}

void StartDateTask::add_task(const std::shared_ptr<Task>& task) {
	auto time = Utils::unixtime_to_string(task->get_start_time());

	status_.entries.emplace_back(time);
}

void StartDateTask::clear() {
	status_.entries.clear();
}
