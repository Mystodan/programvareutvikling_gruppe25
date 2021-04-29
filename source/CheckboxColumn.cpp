#include "CheckboxColumn.h"

#include "EmptyCheckBox.h"
#include "Category.h"

using namespace ftxui;
/**
 * \brief Fills component with all task data
 * \param tasks Tasks to be filled
 */
void CheckboxColumn::fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
	for (const auto& task : tasks) {
		add_task(task);
	}
}


/**
 * \brief Clears/detaches all checkboxes from our component.
 * Will no longer be rendered or execute events
 */
void CheckboxColumn::clear() {
	for (auto* checkbox : checkboxes) {
		checkbox->Detach();
		delete checkbox;
	}
	checkboxes.clear();
}
