#include "DeadlineTask.h"
#include "TimeUtil.h"

/**
 * \brief Fills data from a vector of tasks
 * \param tasks tasks to be added
 */
void DeadlineTask::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	status_.entries.clear();
	for (const auto& task : tasks) {
		add_task(task);
	}
}
/**
 * \brief Adds tasks data to this component
 * \param task task to be added
 */
void DeadlineTask::add_task(const std::shared_ptr<Task>& task) {
	auto time = Utils::unixtime_to_string(task->get_end_time());

	status_.entries.emplace_back(time);
}

/**
 * \brief Clears entries from the component
 */
void DeadlineTask::clear() {
	status_.entries.clear();
}
