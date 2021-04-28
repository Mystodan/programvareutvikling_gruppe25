#include "RecycleBin.h"

#include "TaskManager.h"

using namespace ftxui;

ConfirmationDialog::ConfirmationDialog() {
	Add(&container);

	container.Add(&yes_button);
	container.Add(&no_button);

	yes_button.label = L"Yes";
	no_button.label = L"No";
}

Element ConfirmationDialog::Render() {
	return vbox({ text(L"Are you sure you want to delete all the tasks?"),
		hbox({
			yes_button.Render(),
			no_button.Render()
		})
	});
}

RecycleBin::RecycleBin() {
	Add(&container_);


	// Row (Task name and deleted column)
	container_.Add(&content_);
	content_.Add(&row_container_);
	row_container_.Add(&tasks_);
	row_container_.Add(&deleted_);

	// Button
	container_.Add(&subcontainer_);
	subcontainer_.Add(&delete_button_);
	subcontainer_.Add(&confirmation_dialog_);

	delete_button_.label = L"Recycle";

	delete_button_.on_click = [&]() {
		confirmation_dialog_.TakeFocus();
	};

	confirmation_dialog_.yes_button.on_click = [&]() {
		// Do deletion	
		for (auto &task : tasks_vec) {
			TaskManager::delete_task(task->get_task());
		}
		tasks_vec.clear();

		on_change();

		delete_button_.TakeFocus();
	};
	confirmation_dialog_.no_button.on_click = [&]() {

		delete_button_.TakeFocus();
	};
}

Element RecycleBin::Render() {
	auto menu_win = window(text(L"RecycleBin") | center, tasks_.Render()); // Renders RecycleBin 
	auto deleted_win = window(text(L"Deleted"), deleted_.Render());
	auto delete_button = delete_button_.Render() | size(WIDTH, EQUAL, 8);

	Element document = vbox(hbox({
		menu_win,
		deleted_win
		}), delete_button);

	if (confirmation_dialog_.Focused()) {
		document = dbox({
			document,
			confirmation_dialog_.Render() | clear_under | center
		});
	}
	return document;
}

void RecycleBin::rebuild_data(const std::vector<std::shared_ptr<Task>>& tasks,
	std::function<bool(const std::shared_ptr<Task>&)> predicate, std::function<void()> on_change_) {

	tasks_vec.clear();

	tasks_.entries.clear();

	deleted_.on_change = on_change_;
	deleted_.clear();

	on_change = on_change_;

	// Gets every variable in tasks and updates them if it passes the predicate
	for (const auto& task : tasks) {
		if (predicate(task)) {
			tasks_.entries.push_back(task->get_description());
			deleted_.add_task(task);

			tasks_vec.push_back(task);
		}
	}
}
