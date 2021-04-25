#include "StatusTask.h"

#include "Category.h"
#include "CustomInput.h"
#include "Task.h"

using namespace ftxui;

/**
 * \brief Adds task data to component
 * \param task Task to be added
 */
void StatusTask::add_task(const std::shared_ptr<Task>& task) {
	auto* input = new CustomInput();

	input->placeholder = L"0-100%";

	input->set_content(std::to_wstring(task->get_status()));

	input->on_enter_validate = [=]() {
		auto is_number = [](const std::wstring& s) {
			return !s.empty() && std::find_if(s.begin(),
				s.end(), [](wchar_t c) { return !std::isdigit(c); }) == s.end();
		};
		if (!is_number(input->content)) {
			// TODO: Display error in output window
			return false;	
		}

		// Convert to int and clamp
		auto num = std::clamp<int>(std::stoi(input->content), 0, 100);
		task->set_status(num);

		on_change(); // update for all others

		// TODO: Output success or something to output window
		return true;
	};

	container_.Add(input);
	inputboxes.push_back(input);
}
