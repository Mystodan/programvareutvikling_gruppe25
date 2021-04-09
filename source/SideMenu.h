#pragma once

/*
 *
 */
#include <ftxui/component/container.hpp>
#include <ftxui/component/menu.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include "Tasks.h"
#include "Priority.h"
#include "Completed.h"
#include "RecycleBin.h"
#include "CreateTask.h"
#include "TaskManager.h"

using namespace ftxui;

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
        Rebuild();
    }

    /**
     * \brief This is awful
     */
    void Rebuild() {
        Add(&main_container);
        main_container.Add(&menu);
        menu.entries = {
            L"Tasks",
            L"Priority",
            L"Completed",
            L"Recycle bin",
            L"Create task",
        };

        auto tasks = TaskManager::get_all_tasks();

        // TODO: Add some callback here with criteria to adding the task (like python filter)
        td_Tasks.fill_data(tasks);
        td_Priority.fill_data(tasks);
        td_Completed.fill_data(tasks);

        main_container.Add(&container);
        // TODO: Pass rebuild function as callback to all these that will happen on change for all these controls
        container.Add(&td_Tasks);
        container.Add(&td_Priority);
        container.Add(&td_Completed);
        container.Add(&td_RecycleBin);
        container.Add(&td_CreateTask);
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
