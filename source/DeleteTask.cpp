#include "DeleteTask.h"
#include "EmptyCheckBox.h"

/**
 * \brief Adds a tasks data to this component
 * \param task task to be added
 */
void DeleteTask::add_task(const std::shared_ptr<Task>& task) {
	auto* checkbox = new EmptyCheckBox();

	checkbox->state = task->get_deleted();

	checkbox->on_change = [=]() {
		task->set_deleted(checkbox->state);

		on_change();
	};

	container_.Add(checkbox);
	checkboxes.push_back(checkbox);
}
