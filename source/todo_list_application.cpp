/*
 *  To-do-list application group 25
 *
 *
 *
 *
 *
 */

#include "ftxui/component/container.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "ftxui/component/menu.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/toggle.hpp"
#include "ftxui/screen/string.hpp"
#include "ftxui/component/checkbox.hpp"
#include "ftxui/component/input.hpp"
#include <vector>
#include <iostream>

using namespace ftxui;

class newTask {
public:
    bool isPriority,
        isComplete,
        inBin;
    int  status = 0,
        date,
        id;
    Menu temp;
};

class Tasks : public Component {
public:
    Tasks() {
        Add(&container_);
        container_.Add(&box_1);
        container_.Add(&box_2);
        container_.Add(&box_3);
        box_1.label = L"Build examples";
        box_2.label = L"Build tests";
        box_3.label = L"Use WebAssembly";

    }

    Element Render() override {
        auto menu_win = window(text(L"Tasks") | center, container_.Render());
        return hbox({ menu_win });
    }

private:
    CheckBox box_1;
    CheckBox box_2;
    CheckBox box_3;

    Container container_ = Container::Vertical();
};

class Priority : public Component {
public:
    Priority() {
        Add(&container_);
        Add(&container_2);
        container_.Add(&task_);
        container_2.Add(&status_);

        task_.entries = {
            L"Task 4",
            L"Task 5",
            L"Task 6",
        };
        status_.entries = {
            L"Status1",
            L"Status2",
            L"Status3",
        };
    }
    Element Render() override {
        auto task_win = window(text(L"Priority") | center, task_.Render());
        auto status_win = window(text(L"Status") | center, status_.Render());
        return hbox({
            task_win,
            status_win,
        });
    }

    std::function<void()> on_enter = []() {};

private:
    Menu task_;
    Menu status_;
    Container container_ = Container::Vertical();
    Container container_2 = Container::Vertical();
};

class Completed : public Component {
public:
    Completed() {
        Add(&container_);
        container_.Add(&task_);

        task_.entries = {
            L"Task 7",
            L"Task 8",
            L"Task 9",
            L"Task 10",
        };
    }
    Element Render() override {
        auto menu_win = window(text(L"Completed") | center, task_.Render()); // Makes window around menu
        return vbox({ menu_win });
    }

    std::function<void()> on_enter = []() {};

private:
    Menu task_;
    Container container_ = Container::Vertical();
};

class RecycleBin : public Component {
public:
    RecycleBin() {
        Add(&container_);
        container_.Add(&task_);

        task_.entries = {
            L"Task 7",
            L"Task 8",
            L"Task 9",
            L"Task 10",
        };
    }
    Element Render() override {
        auto menu_win = window(text(L"RecycleBin") | center, task_.Render()); // Makes window around menu
        return vbox({ menu_win });
    }

    std::function<void()> on_enter = []() {};

private:
    Menu task_;
    Container container_ = Container::Vertical();
};

class CreateTask : public Component {
public:
    CreateTask() {
        Add(&container);
        container.Add(&input_1);
        container.Add(&box_2);
        container.Add(&input_3);
        container.Add(&input_4);
        container.Add(&input_5);
        box_2.label = L"(X = Priority)";
    }

    std::function<void()> on_enter = []() {};

private:
    Container container = Container::Vertical();
    Input input_1;
    CheckBox box_2;
    Input input_3;
    Input input_4;
    Input input_5;

    Element Render() override {
       return border(vbox({
            hbox({text(L"Insert name of task: "), input_1.Render()}),
            hbox({text(L"Choose priority of task: "), box_2.Render()}),
            hbox({text(L"Insert status for task (0-100%): "), input_3.Render()}),
            hbox({text(L"Set start-date for task (dd.mm.yy): "), input_4.Render()}),
            hbox({text(L"Set deadline for task (dd.mm.yy): "), input_5.Render()}),
            hbox(text(L"                         Confirm  Cancel")), // Will be changed to buttons later
            }));
    }
};

class Tab : public Component {
public:
    Container main_container = Container::Horizontal();
    Container container = Container::Tab(&menu.selected);
    Menu menu;

    Tasks       td_Tasks;
    Priority    td_Priority;
    Completed   td_Completed;
    RecycleBin  td_RecycleBin;
    CreateTask  td_CreateTask;

    Tab() {
        Add(&main_container);
        main_container.Add(&menu);
        menu.entries = {
            L"Tasks",
            L"Priority",
            L"Completed",
            L"Recycle bin",
            L"Create task"
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

std::vector<newTask> gTask[];

int main(int argc, const char* argv[]) {
    auto screen = ScreenInteractive::TerminalOutput();
    Tab tab;
    screen.Loop(&tab);
    return 0;
}