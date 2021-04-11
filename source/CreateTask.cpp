#include "CreateTask.h"
#include "Task.h"
#include "TaskManager.h"
#include "TimeUtil.h"

CreateTask::CreateTask() {
	Add(&container);				     // Adds a new container 
	container.Add(&description_input_);
	container.Add(&priority_box);
	container.Add(&status_input_);
	container.Add(&start_time_input_);
	container.Add(&end_time_input_);
	container.Add(&confirm_button);

	priority_box.label = L"(X = Priority)";
	confirm_button.label = L"Confirm";

	confirm_button.on_click = [&]() {
		auto is_number = [](const std::wstring& s) {
			return !s.empty() && std::find_if(s.begin(),
			                                  s.end(), [](wchar_t c) { return !std::isdigit(c); }) == s.end();
		};

		output_window_.entries.clear();

		bool valid_data = true;

		if (status_input_.content.empty()) {
			output_window_.entries.emplace_back(L"The task cannot have an empty status");
			valid_data = false;
		}

		if (!is_number(status_input_.content)) {
			output_window_.entries.emplace_back(L"The status must be a number");
			valid_data = false;
		}

		std::wstring description = description_input_.content;
		if (description.empty()) {
			output_window_.entries.emplace_back(L"The task needs to have a name");
			valid_data = false;
		}

		std::wstring start_time_str = start_time_input_.content;
		if (start_time_str.empty()) {
			output_window_.entries.emplace_back(L"The task needs to have a start time");
			valid_data = false;
		}

		std::wstring end_time_str = end_time_input_.content;
		if (end_time_str.empty()) {
			output_window_.entries.emplace_back(L"The task needs to have a end time");
			valid_data = false;
		}

		if (valid_data) {
			// This is to be filled in
			TaskDB task;

			task.description = description;

			int start_time = Utils::string_to_unixtime(start_time_input_.content);
			int end_time = Utils::string_to_unixtime(end_time_input_.content);

			task.start_time = start_time;
			task.end_time = end_time;
			task.priority = static_cast<int>(priority_box.state);

			task.status = stoi(status_input_.content);

			TaskManager::add_task(task);

			on_change();

			// Clear data
			description_input_.content.clear();
			status_input_.content.clear();
			start_time_input_.content.clear();
			end_time_input_.content.clear();
		}
	};
}

Element CreateTask::Render() {

	auto input_win = window(text(L"Output"), hbox({output_window_.Render(),}));

	return border(vbox({
		hbox({text(L"Insert name of task: "), description_input_.Render()}),
		hbox({text(L"Choose priority of task: "), priority_box.Render()}),
		hbox({text(L"Insert status for task (0-100%): "), status_input_.Render()}),
		hbox({text(L"Set start-date for task (dd.mm.yy): "), start_time_input_.Render()}),
		hbox({text(L"Set deadline for task (dd.mm.yy): "), end_time_input_.Render()}),
		hbox({confirm_button.Render()}),
		vbox({input_win | size(WIDTH, EQUAL, 60),}),
	}));
}
