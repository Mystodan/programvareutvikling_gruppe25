#include "StartDateTask.h"

#include "Task.h"
#include "TimeUtil.h"

using namespace ftxui;
/**
 * \brief Adds task data to component and converts unix time (int) to a string
 * \param task Task to be added
 */
void StartDateTask::add_task(const std::shared_ptr<Task>& task) {
	auto* input = new CustomInput();

	input->placeholder = L"dd.mm.yy"; 

	auto time = Utils::unixtime_to_string(task->get_start_time());
	input->set_content(time);

	input->on_enter_validate = [=]() {
		clear_output();

		const auto conv_time = Utils::string_to_unixtime(input->content);
		if (conv_time == -1) {
			add_error(L"Invalid time format, try again");
			return false;
		}
		task->set_start_time(conv_time);

		on_change(); // update for all others

		add_output(L"Successfully set new date\n");

		return true;
	};

	container_.Add(input);
	inputboxes.push_back(input);
}
