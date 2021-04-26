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
#ifdef DEBUG
		OutputDebugStringW((std::wstring(L"Pressed enter with ") + task->get_description() + std::wstring(L"\n")).c_str());
#endif
		task->set_description(input->content);
		on_change(); // update for all others

		// TODO: Output to output window
		return true;
	};

	container_.Add(input);
	inputboxes.push_back(input);
}
