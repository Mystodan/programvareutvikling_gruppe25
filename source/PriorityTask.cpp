#include "PriorityTask.h"

#include "EmptyCheckBox.h"
#include "Category.h"

using namespace ftxui;
/**
 * \brief Fills component with all task data
 * \param tasks Tasks to be filled
 */
void PriorityTask::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	for (const auto& task : tasks) {
		add_task(task);
	}
}

/**
 * \brief Adds a task's data to the component,
 * also sets the callback
 * \param task Task to be added
 */
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

/**
 * \brief Clears/detaches all checkboxes from our component.
 * Will no longer be rendered or execute events
 */
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
