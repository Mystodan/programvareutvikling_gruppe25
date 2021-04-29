#include "BaseTask.h"
#include <Windows.h>
#include "TimeUtil.h"

using namespace ftxui;

void BaseTask::rebuild_data(const std::vector<std::shared_ptr<Task>>& tasks,
                            std::function<bool(const std::shared_ptr<Task>&)> predicate,
                            std::function<void()> on_change) {


	const auto set_callbacks_and_clear = [&](InputColumn* col) {
		col->add_output = [=](const std::wstring& str) { add_output(str); };
		col->add_error = [=](const std::wstring& str) { add_error(str); };
		col->clear_output = [=]() { clear_output(); };
		col->on_change = on_change;

		col->clear();
	};

	set_callbacks_and_clear(&task_);
	set_callbacks_and_clear(&startDate_);
	set_callbacks_and_clear(&deadline_);
	set_callbacks_and_clear(&status_);

	// Not an input column
	priority_.on_change = on_change;
	priority_.clear();

	deleted_.on_change = on_change;
	deleted_.clear();

	// Gets every variable in tasks and updates them if it passes the predicate
	for (const auto& task : tasks) {
		if (predicate(task)) {
			task_.add_task(task);
			priority_.add_task(task);
			startDate_.add_task(task);
			deadline_.add_task(task);
			status_.add_task(task);
			deleted_.add_task(task);
		}
	}
}


/**
 * \brief Renders BaseTask component
 * \return Element to be rendered
 */
Element BaseTask::Render() {
	auto task_win = window(text(L"Task(F1)") | center, task_.Render());
	auto priority_win = window(text(L"Priority(F2)") | center | size(WIDTH, EQUAL, 12), priority_.Render());
	auto status_win = window(text(L"Status(F3)") | center, status_.Render());
	auto startDate_win = window(text(L"Start-date(F4)") | center, startDate_.Render());
	auto deadline_win = window(text(L"Deadline(F5)") | center, deadline_.Render());
	auto deleted_win = window(text(L"Deleted"), deleted_.Render());
	auto output_win = window(text(L"Output"), output_window_.Render());

	// Returns a horizontal container displaying all the columns
	return vbox(hbox({
		task_win,
		priority_win,
		status_win,
		startDate_win,
		deadline_win,
		deleted_win
	}), output_win);
}

/**
 * \brief Adds output to the output window with a green color
 * \param output to be added to the output window
 */
void BaseTask::add_output(const std::wstring& output) {
	output_window_.selected_style = color(Color::Green);
	output_window_.entries.push_back(output);
}

/**
 * \brief Adds error output to the output window with a red color
 * \param error_message 
 */
void BaseTask::add_error(const std::wstring& error_message) {
	output_window_.selected_style = color(Color::Red);
	output_window_.entries.push_back(error_message);
}

/**
 * \brief Clears the output window 
 */
void BaseTask::clear_output() {
	output_window_.entries.clear();
}

/**
 * \brief Checks if the list of rows is empty
 * \return true if empty
 */
bool BaseTask::is_empty() const {
	return task_.inputboxes.empty();
}

