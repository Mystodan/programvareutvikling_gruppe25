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
	};
	main_container.Add(&container);

	container.Add(&td_Tasks);
	container.Add(&td_Priority);
	container.Add(&td_Completed);
	container.Add(&td_RecycleBin);
	container.Add(&td_CreateTask);


	// Fill the map
	// F1: OP
	// F2: OQ
	// TODO: Change to F1
	key_map["OP"] = SortBy::TASKNAME;
	key_map["p"] = SortBy::PRIORITY;
	key_map["s"] = SortBy::STATUS;
	key_map["b"] = SortBy::STARTDATE;
	key_map["d"] = SortBy::DEADLINE;


	on_change = [this]() { RebuildDataEntries(); };

	RebuildDataEntries();
}

/**
 * \brief Rebuilds all the data entries when a change happens to one of the data entries (tasks)
 */
void SideMenu::RebuildDataEntries() {
	auto tasks = TaskManager::get_all_tasks();

	sort_tasks(tasks);

	// On change function to be passed onto the children to call when a change happens in them
	// It will then call this rebuild function we are currently in

	// Add the tasks and supply them with a predicate for adding them or not and also the on_change callback
	td_Tasks.rebuild_data(tasks, [](const std::shared_ptr<Task>& task) {
		return true;
	}, on_change);

	td_Priority.rebuild_data(tasks, [](const std::shared_ptr<Task>& task) {
		return task->get_priority() != 0;
	}, on_change);

	td_Completed.rebuild_data(tasks, [](const std::shared_ptr<Task>& task) {
		return task->get_status() == 100;
	}, on_change);

	td_CreateTask.on_change = on_change;
}

/**
 * \brief Builds render element for this component
 * \return Element to be rendered
 */
Element SideMenu::Render() {
	return vbox({
		text(L"To-do-list") | bold | hcenter,
		hbox({
			hbox({window(text(L"Side Menu") | center, menu.Render()) | center, container.Render()}),
		}) | border,
	});
}


void SideMenu::sort_tasks(std::vector<std::shared_ptr<Task>>& tasks) const {

	std::function<bool(std::shared_ptr<Task>, std::shared_ptr<Task>)> pred;

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
