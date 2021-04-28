#include "PriorityTask.h"

#include "EmptyCheckBox.h"

void PriorityTask::add_task(const std::shared_ptr<Task>& task) {
	auto* checkbox = new EmptyCheckBox();

	checkbox->state = task->get_priority();

	checkbox->on_change = [=]() {
		task->set_priority(checkbox->state);

		on_change();
	};

	container_.Add(checkbox);
	checkboxes.push_back(checkbox);
}
