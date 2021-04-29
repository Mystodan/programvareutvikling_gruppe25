#include "SideMenu.h"

#include "Task.h"
#include <Windows.h>

/**
 * \brief Fills the component with all it's children and containers
 */
SideMenu::SideMenu() {
	Add(&main_container);
	main_container.Add(&menu);
	menu.entries = {
		L"Tasks",
		L"Priority",
		L"Completed",
		L"Recycle bin",
		L"Create task",
		L"Help",
	};
	main_container.Add(&container);

	container.Add(&td_Tasks);
	container.Add(&td_Priority);
	container.Add(&td_Completed);
	container.Add(&td_RecycleBin);
	container.Add(&td_CreateTask);
	container.Add(&help_window);


	// Fill the map
	key_map["OP"] = SortBy::TASKNAME;		// F1
	key_map["OQ"] = SortBy::PRIORITY;		// F2
	key_map["OS"] = SortBy::STATUS;		// F3
	key_map["[15~"] = SortBy::STARTDATE;	// F4
	key_map["[17~"] = SortBy::DEADLINE;	// F5

	on_change = [this]() { RebuildDataEntries(); };

	RebuildDataEntries();
}

/**
 * \brief Rebuilds all the data entries when a change happens to one of the data entries (tasks)
 */
void SideMenu::RebuildDataEntries() {
	try {
		auto tasks = TaskManager::get_all_tasks();

		sort_tasks(tasks);

		// Helper to check if the tab is now empty
		// If it is, we set focus back to the sidemenu
		const auto check_empty_take_focus = [&](auto& task_tab) {
			if (task_tab.is_empty() && task_tab.Focused()) {
				// Give focus to menu (sidebar)
				menu.TakeFocus();
			}
		};

		// On change function to be passed onto the children to call when a change happens in them
		// It will then call this rebuild function we are currently in

		// Add the tasks and supply them with a predicate for adding them or not and also the on_change callback
		td_Tasks.rebuild_data(tasks, [](const std::shared_ptr<Task>& task) {
			// All tasks that are not set to be deleted
			return task->get_deleted() == 0;
			}, on_change);
		check_empty_take_focus(td_Tasks);


		td_Priority.rebuild_data(tasks, [](const std::shared_ptr<Task>& task) {
			// Priority is set and not deleted
			return task->get_priority() == 1 && task->get_deleted() == 0;
			}, on_change);
		check_empty_take_focus(td_Priority);

		td_Completed.rebuild_data(tasks, [](const std::shared_ptr<Task>& task) {
			// Status is 100% and not deleted
			return task->get_status() == 100 && task->get_deleted() == 0;
			}, on_change);
		check_empty_take_focus(td_Completed);

		td_RecycleBin.rebuild_data(tasks, [](const std::shared_ptr<Task>& task) {
			// Is deleted
			return task->get_deleted() == 1;
			}, on_change);
		check_empty_take_focus(td_RecycleBin);

		td_CreateTask.on_change = on_change;
	}
	catch (std::exception& e) {
		auto err = e.what();
		std::cout << err << "\n";
	}
}

/**
 * \brief Builds render element for this component
 * \return Element to be rendered
 */
Element SideMenu::Render() {
	auto s = size(Direction::WIDTH, Constraint::EQUAL, 20);
	return vbox({
		text(L"NTNDU") | bold | hcenter,
		hbox({
			hbox({window(text(L"Side Menu") | center, menu.Render()) | s | center, container.Render()}),
		}) | border,
	});
}


/**
 * \brief Sorts the tasks vector according to the active sort order and type
 * \param tasks to be sorted
 */
void SideMenu::sort_tasks(std::vector<std::shared_ptr<Task>>& tasks) const {

	std::function<bool(std::shared_ptr<Task>, std::shared_ptr<Task>)> pred;

	// Assign predicate function based on what we want to sort by
	switch(sort_by) {
	case SortBy::TASKNAME: 
		pred = [*this](std::shared_ptr<Task> lhs, std::shared_ptr<Task> rhs) {
			if (sort_order == SortOrder::ASCENDING)
				return lhs->get_description()  < rhs->get_description();

			return lhs->get_description() > rhs->get_description();
		};
		break;
	case SortBy::PRIORITY: 
		pred = [*this](std::shared_ptr<Task> lhs, std::shared_ptr<Task> rhs) {
			if (sort_order == SortOrder::ASCENDING)
				return lhs->get_priority() < rhs->get_priority();

			return lhs->get_priority() > rhs->get_priority();
		};
		break;
	case SortBy::STATUS: 
		pred = [*this](std::shared_ptr<Task> lhs, std::shared_ptr<Task> rhs) {
			if (sort_order == SortOrder::ASCENDING) {
				return lhs->get_status() < rhs->get_status();
			}

			return lhs->get_status() > rhs->get_status();
		};
		break;
	case SortBy::STARTDATE: 
		pred = [*this](std::shared_ptr<Task> lhs, std::shared_ptr<Task> rhs) {
			if (sort_order == SortOrder::ASCENDING)
				return lhs->get_start_time() < rhs->get_start_time();

			return lhs->get_start_time() > rhs->get_start_time();
		};
		break;
	case SortBy::DEADLINE: 
		pred = [*this](std::shared_ptr<Task> lhs, std::shared_ptr<Task> rhs) {
			if (sort_order == SortOrder::ASCENDING)
				return lhs->get_end_time() < rhs->get_end_time();

			return lhs->get_end_time() > rhs->get_end_time();
		};
		break;
	default: 
		return; // Just return, no sorting needed/can be done
	}

	std::sort(tasks.begin(), tasks.end(), pred);
}

/**
 * \brief Callback for when an event happens in the UI.
 * Handles sort order and type based on the event (input)
 * \param event thrown from the UI
 * \return true if we captured the event in this component
 */
bool SideMenu::OnEvent(ftxui::Event event) {
	const auto flip_sort = [this]() {
		if (sort_order == SortOrder::ASCENDING) {
			sort_order = SortOrder::DESCENDING;
		} else {
			sort_order = SortOrder::ASCENDING;
		}
	};

	if (const auto it = key_map.find(event.input()); it != key_map.end()) {

		// Only flip it if it is already selected/active
		if (const auto [key, _sort_by] = *it; sort_by == _sort_by) {
			flip_sort();
		} else {
			sort_by = _sort_by;
		}

		on_change();
		return true;
	}

	return Component::OnEvent(event);
}
