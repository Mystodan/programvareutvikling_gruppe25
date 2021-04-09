#pragma once

/*
 *
 */

#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "tasks.h"
#include "Priority.h"
#include "PriorityTask.h"
#include "Completed.h"
#include "RecycleBin.h"
#include "CreateTask.h"


using namespace ftxui;

/*
 *
 */

class SideMenu : public Component {
public:
    Container main_container = Container::Horizontal();
    Container container = Container::Tab(&menu.selected);

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
