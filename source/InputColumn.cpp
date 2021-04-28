#include "InputColumn.h"

#include "EmptyCheckBox.h"
#include "Category.h"
#include <Windows.h>

using namespace ftxui;

/**
 * \brief Fills component with all task data
 * \param tasks Tasks to be filled
 */
void InputColumn::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	for (const auto& task : tasks) {
		add_task(task);
	}
}

/**
 * \brief Clears/detaches all checkboxes from our component.
 * Will no longer be rendered or execute events
 */
void InputColumn::clear() {
	for (auto* input : inputboxes) {
		//delete checkbox;
		input->Detach();
	}
}

//ftxui::Element InputColumn::Render() {
//	return container_.Render();
//}
