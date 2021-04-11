#include "StartDateTask.h"

#include "Task.h"
#include "TimeUtil.h"

/**
 * \brief Fills component with task data
 * \param tasks Tasks to be added
 */
void StartDateTask::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	status_.entries.clear();
	for (const auto& task : tasks) {
		add_task(task);
	}
}

/**
 * \brief Adds task data to component and converts unix time (int) to a string
 * \param task Task to be added
 */
void StartDateTask::add_task(const std::shared_ptr<Task>& task) {
	auto time = Utils::unixtime_to_string(task->get_start_time());

	status_.entries.emplace_back(time);
}

/**
 * \brief Clears all all entries from component
 */
void StartDateTask::clear() {
	status_.entries.clear();
}
