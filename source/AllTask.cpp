#include "AllTask.h"

#include "EmptyCheckBox.h"
#include "Category.h"
#include <Windows.h>

using namespace ftxui;

/**
 * \brief Adds a task's data to the component,
 * also sets the callback
 * \param task Task to be added
 */
void AllTask::add_task(const std::shared_ptr<Task>& task) {
	auto* input = new CustomInput();

	input->placeholder = L"Task description";
	input->set_content(task->get_description());

	input->on_enter_validate = [=]() {
		clear_output();

		const auto old_description = task->get_description();
		if (old_description == input->content) {

			return false;
		}

		task->set_description(input->content);
		on_change(); // update for all others

		clear_output();
		add_output(L"Successfully changed the description");

		return true;
	};

	container_.Add(input);
	inputboxes.push_back(input);
}
