#include "PriorityTask.h"

#include "EmptyCheckBox.h"
#include "Category.h"

void PriorityTask::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	for (const auto& task : tasks) {
		auto* checkbox = new EmptyCheckBox();

		checkbox->state = task->get_category().get_priority();

		checkbox->on_change = [=]() {
			task->get_category().set_priority(checkbox->state);
		};

		container_.Add(checkbox);
	}
}
