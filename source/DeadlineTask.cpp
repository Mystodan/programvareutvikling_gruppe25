#include "DeadlineTask.h"
#include "TimeUtil.h"

using namespace ftxui;

/**
 * \brief Adds tasks data to this component
 * \param task task to be added
 */
void DeadlineTask::add_task(const std::shared_ptr<Task>& task) {
	auto* input = new CustomInput();

	input->placeholder = L"dd.mm.yy"; 

	auto time = Utils::unixtime_to_string(task->get_end_time());
	input->set_content(time);

	input->on_enter_validate = [=]() {

		auto time = Utils::string_to_unixtime(input->content);

		if (time == -1) {
			// TODO: output error
			return false;
		}
		task->set_end_time(time);

		on_change(); // update for all others

		// TODO: Output success or something to output window
		return true;
	};

	container_.Add(input);
	inputboxes.push_back(input);
}
