#include "DeadlineTask.h"

void DeadlineTask::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	status_.entries.clear();
	for (const auto& task : tasks) {
		add_task(task);
	}
}

void DeadlineTask::add_task(const std::shared_ptr<Task>& task) {
	wchar_t buffer[9];
	time_t unixTime = task->get_end_time();
	struct tm tm_;
	localtime_s(&tm_, &unixTime);
	wcsftime(buffer, sizeof(buffer), L"%d.%m.%y", &tm_);
	status_.entries.emplace_back(buffer);
}

void DeadlineTask::clear() {
	status_.entries.clear();
}
