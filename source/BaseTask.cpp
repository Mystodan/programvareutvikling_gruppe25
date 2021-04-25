#include "BaseTask.h"
#include <Windows.h>

using namespace ftxui;

void BaseTask::rebuild_data(const std::vector<std::shared_ptr<Task>>& tasks,
                            std::function<bool(const std::shared_ptr<Task>&)> predicate,
                            std::function<void()> on_change) {
	task_.on_change = on_change;
	priority_.on_change = on_change;

	task_.clear(); // Clears task_.entries

	priority_.clear();    // Clears priority_
	startDate_.clear();   // Clears startDate_
	deadline_.clear();    // Clears deadline_
	status_.clear();      // Clears status_


	// Gets every variable in tasks and updates them if it passes the predicate
	for (const auto& task : tasks) {
		if (predicate(task)) {
			task_.add_task(task);
			priority_.add_task(task);
			startDate_.add_task(task);
			deadline_.add_task(task);
			status_.add_task(task);
		}
	}
}

// Renders the elements with a window around each container
Element BaseTask::Render() {
	auto task_win = window(text(L"Task (F1)") | center, task_.Render());
	auto priority_win = window(text(L"Priority (P)") | center, priority_.Render());
	auto status_win = window(text(L"Status (S)") | center, status_.Render());
	auto startDate_win = window(text(L"Start-date (B)") | center, startDate_.Render());
	auto deadline_win = window(text(L"Deadline (D)") | center, deadline_.Render());
	// Returns a horizontal container displaying all the columns
	return hbox({
		task_win,
		priority_win,
		status_win,
		startDate_win,
		deadline_win,
	});
}

