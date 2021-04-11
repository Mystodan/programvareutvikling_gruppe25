#include "SideMenu.h"

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

	RebuildDataEntries();
}

/**
 * \brief Rebuilds all the data entries when a change happens to one of the data entries (tasks)
 */
void SideMenu::RebuildDataEntries() {
	auto tasks = TaskManager::get_all_tasks();

	// On change function to be passed onto the children to call when a change happens in them
	// It will then call this rebuild function we are currently in
	auto on_change = [this]() { RebuildDataEntries(); };

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
