#include "PriorityTask.h"

#include "EmptyCheckBox.h"
#include "Category.h"

using namespace ftxui;
void PriorityTask::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	for (const auto& task : tasks) {
		add_task(task);
	}
}

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

void PriorityTask::clear() {
	for (auto* checkbox : checkboxes) {
		//delete checkbox;
		checkbox->Detach();
	}
}

//ftxui::Element PriorityTask::Render() {
//	Elements elements;
//	for (auto* checkbox : checkboxes) {
//		elements.push_back(checkbox->Render());
//	}
//	return vbox(elements);
//}
