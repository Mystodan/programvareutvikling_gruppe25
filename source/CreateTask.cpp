#include "CreateTask.h"
#include "Task.h"
#include "TaskManager.h"
#include "TimeUtil.h"

CreateTask::CreateTask() {
	Add(&container);                                  // Adds relevant containers from library
	container.Add(&description_input_);
	container.Add(&priority_box);
	container.Add(&status_input_);
	container.Add(&start_time_input_);
	container.Add(&end_time_input_);
	container.Add(&confirm_button);

	priority_box.label = L"(X = Priority)";           // Text is shown to user to explain that when box is marked with X, it is a priority
	confirm_button.label = L"Confirm";                // Text content inside confirm button

	confirm_button.on_click = [&]() {                 // When confirm button is clicked, do the following:
		auto is_number = [](const std::wstring& s) {
			return !s.empty() && std::find_if(s.begin(),
				s.end(), [](wchar_t c) { return !std::isdigit(c); }) == s.end();
		};

		output_window_.entries.clear();

		bool valid_data = true;

		// If status input is empty, valid_data is set to false and corresponding error message is shown
		if (status_input_.content.empty()) {
			output_window_.entries.emplace_back(L"The task cannot have an empty status");
			valid_data = false;
		}

		// If status input is not a number, valid_data is set to false and corresponding error message is shown
		if (!is_number(status_input_.content)) {
			output_window_.entries.emplace_back(L"The status must be a number");
			valid_data = false;
		}

		// If description is empty, valid_data is set to false and corresponding error message is shown
		std::wstring description = description_input_.content;
		if (description.empty()) {
			output_window_.entries.emplace_back(L"The task needs to have a name");
			valid_data = false;
		}

		// If start time is empty, valid_data is set to false and corresponding error message is shown
		std::wstring start_time_str = start_time_input_.content;
		if (start_time_str.empty()) {
			output_window_.entries.emplace_back(L"The task needs to have a start time");
			valid_data = false;
		}

		// If end time is empty, valid_data is set to false and corresponding error message is shown
		std::wstring end_time_str = end_time_input_.content;
		if (end_time_str.empty()) {
			output_window_.entries.emplace_back(L"The task needs to have a end time");
			valid_data = false;
		}

		// If all data is valid, data gets filled in and adds a new task
		if (valid_data) {
			TaskDB task;

			task.description = description; // Adds task description

			int start_time = Utils::string_to_unixtime(start_time_input_.content); // Converts start_date string input to unixTime, makes it easier to add sorting functionality
			int end_time = Utils::string_to_unixtime(end_time_input_.content); // Converts end_date string input to unixTime, makes it easier to add sorting functionality

			task.start_time = start_time; // Adds task start time
			task.end_time = end_time; // Adds task end time
			task.priority = static_cast<int>(priority_box.state); // Adds task priority
			task.deleted = false;

			task.status = stoi(status_input_.content); // Adds task status

			TaskManager::add_task(task); // Adds new task to database

			on_change();

			// Clears input data
			description_input_.content.clear();
			status_input_.content.clear();
			start_time_input_.content.clear();
			end_time_input_.content.clear();
		}
	};
}

Element CreateTask::Render() {

	auto input_win = window(text(L"Output"), hbox({ output_window_.Render(), }));

	return border(vbox({
		// TODO: separation with set width
		hbox({text(L"Insert name of task: "), description_input_.Render()}), // User can write task name
		hbox({text(L"Choose priority of task: "), priority_box.Render()}), // User can choose priority
		hbox({text(L"Insert status for task (0-100%): "), status_input_.Render()}), // User can set a status for task
		hbox({text(L"Set start-date for task (dd.mm.yy): "), start_time_input_.Render()}), // User can set start-date for task
		hbox({text(L"Set deadline for task (dd.mm.yy): "), end_time_input_.Render()}), // User can set deadline for task 
		hbox({confirm_button.Render()}),
		vbox({input_win | size(WIDTH, EQUAL, 60),}),
		}));
}
