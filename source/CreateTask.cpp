#include "CreateTask.h"
#include "Task.h"
#include "TaskManager.h"
#include "TimeUtil.h"

CreateTask::CreateTask() {
	Add(&container);                                  // Adds relevant containers from library
	container.Add(&description_input_);
	container.Add(&start_time_input_);
	container.Add(&end_time_input_);
	container.Add(&confirm_button);

	//priority_box.label = L"(X = Priority)";           // Text is shown to user to explain that when box is marked with X, it is a priority
	confirm_button.label = L"Confirm";                // Text content inside confirm button

	confirm_button.on_click = [&]() {                 // When confirm button is clicked, do the following:
		output_window_.entries.clear();

		bool valid_data = true;

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
			//task.priority = static_cast<int>(priority_box.state); // Adds task priority
			task.priority = 0;
			task.deleted = false;

			task.status = 0;
			

			TaskManager::add_task(task); // Adds new task to database

			on_change();

			// Clears input data
			description_input_.content.clear();
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
		hbox({text(L"Set start-date for task (dd.mm.yy): "), start_time_input_.Render()}), // User can set start-date for task
		hbox({text(L"Set deadline for task (dd.mm.yy): "), end_time_input_.Render()}), // User can set deadline for task 
		hbox({confirm_button.Render()}),
		vbox({input_win | size(WIDTH, EQUAL, 60),}),
		}));
}
