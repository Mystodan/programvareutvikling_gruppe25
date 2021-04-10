#pragma once

/*
 *
 */
#include <functional>

#include <ftxui/component/container.hpp>
#include <ftxui/component/menu.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include "Category.h"
#include "Tasks.h"
#include "Priority.h"
#include "Completed.h"
#include "RecycleBin.h"
#include "CreateTask.h"
#include "TaskManager.h"
#include "TaskStatus.h"

//using namespace ftxui;

class SideMenu : public Component {
public:
    Container main_container = Container::Horizontal();
    Container container = Container::Tab(&menu.selected);

    // TODO: Restructure so they are all the same class (except recyclebin and createtask) but with some different properties
    // Makes it easier to add new code for all of them and the layout is the same on all
    Menu        menu;
    Tasks       td_Tasks;
    Priority    td_Priority;
    Completed   td_Completed;
    RecycleBin  td_RecycleBin;
    CreateTask  td_CreateTask;

    SideMenu() {
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
     * \brief This is awful
     */
    void RebuildDataEntries() {
		auto tasks = TaskManager::get_all_tasks();

		auto on_change = [this]() { RebuildDataEntries(); };
    	
		// Add the tasks and supply them with a predicate for adding them or not and also the on_change callback
		td_Tasks.rebuild_data(tasks, [](const std::shared_ptr<Task>& task) {
			return true;
			}, on_change);

		td_Priority.rebuild_data(tasks, [](const std::shared_ptr<Task>& task) {
			return task->get_priority() != 0;
			}, on_change);

		td_Completed.rebuild_data(tasks, [](const std::shared_ptr<Task>& task) {
			// NB! This is an example
			return task->get_status() == 100;
			}, on_change);

		td_CreateTask.on_change = on_change;
	}

    Element Render() override {
        return vbox({
            text(L"To-do-list") | bold | hcenter,
                hbox({
                    hbox({ window(text(L"Side Menu") | center, menu.Render()) | center, container.Render()}),
                }) | border,
            });
    }
};
