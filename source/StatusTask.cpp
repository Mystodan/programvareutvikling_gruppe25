#include "StatusTask.h"

#include "Category.h"
#include "EmptyCheckBox.h"
#include "Task.h"

/**
 * \brief Fills component with task data
 * \param tasks Tasks to be added
 */
void StatusTask::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	for (const auto& task : tasks) {
		add_task(task);
	}
}

/**
 * \brief Adds task data to component
 * \param task Task to be added
 */
void StatusTask::add_task(const std::shared_ptr<Task>& task) {
	status_.entries.push_back(std::to_wstring(task->get_status()));
}

/**
 * \brief Clears all all entries from component
 */
void StatusTask::clear() {
	status_.entries.clear();
}
