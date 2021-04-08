/*
 * To-do-list application group 25
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

#include "EmptyCheckBox.h"
#include "UsersTasks.h"
#include "Task.h"
#include "User.h"
#include "Category.h"

using namespace ftxui;

/*
 *
 */

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

/*
 *
 */

class PriorityTask : public Component {
public:
    PriorityTask() {
        Add(&container_);
    }

    void fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
        for (const auto& task : tasks) {
            auto* checkbox = new EmptyCheckBox();

            checkbox->state = task->get_category().get_priority();

			checkbox->on_change = [=]() {
				task->get_category().set_priority(checkbox->state);
			};

            container_.Add(checkbox);
        }
    }

    std::function<void()> on_enter = []() {};

private:
    Container container_ = Container::Vertical();
};

/*
 *
 */

class StatusTask : public Component {
public:
    StatusTask() {
        Add(&container_);

        container_.Add(&status_);


        status_.entries = {
               L"75%",                  //Read Task1 status
               L"50%",
               L"0%",
        };
    }
    std::function<void()> on_enter = []() {};

private:
    Menu status_;
    Container container_ = Container::Vertical();
};

/*
 *
 */

class StartDateTask : public Component {
public:
    StartDateTask() {
        Add(&container_);
        container_.Add(&status_);

        status_.entries = {
               L"01.04.21",             //Read Task1 StartDate
               L"01.04.21",
               L"01.04.21",
               L"02.04.21",
        };
    }
    std::function<void()> on_enter = []() {};

private:
    Menu status_;
    Container container_ = Container::Vertical();
};

/*
 *
 */

class DeadlineTask : public Component {
public:
    DeadlineTask() {
        Add(&container_);
        container_.Add(&status_);

        status_.entries = {
               L"14.04.21",         //Read Task1 Deadline
               L"16.04.21",
               L"17.04.21",
               L"18.04.21",
        };
    }
    std::function<void()> on_enter = []() {};

private:
    Menu status_;
    Container container_ = Container::Vertical();
};

/* 
 * 
 */

// TODO: figure this out and have one vector of these base components in the tab class and then call fill_data from those base components to fill from vec
class BaseTask : public Component {
public:
    void fill_data(const std::vector<Task>& tasks);
};

class Tasks : public Component {
public:
    Tasks() {

        auto tasks = UserTasksManager::get_all_tasks();

        Add(&container_);                   //Adds a new container
        container_.Add(&task_);             //Adds a task container
        container_.Add(&priority_);         //Adds a priority container
        container_.Add(&status_);           //Adds a status container
        container_.Add(&startDate_);        //Adds a startDate container
        container_.Add(&deadline_);         //Adds a deadline container

        priority_.fill_data(tasks);

        task_.entries = {                   //Defines the entries in the task container
            L"Task 1",                      //Read Task1 Name
            L"Task 2",                      //Read Task2 Name
            L"Task 3",                      //Read Task3 Name
        };
    }

    Element Render() override {
        auto task_win = window(text(L"Task") | center, task_.Render());
        auto priority_win = window(text(L"Priority") | center, priority_.Render());
        auto status_win = window(text(L"Status") | center, status_.Render());
        auto startDate_win = window(text(L"Start-date") | center, startDate_.Render());
        auto deadline_win = window(text(L"Deadline") | center, deadline_.Render());
        return hbox({
            task_win,
            priority_win,
            status_win,
            startDate_win,
            deadline_win,
            });

    }
    std::function<void()> on_enter = []() {};

private:
    Menu task_;
    StatusTask status_;
    PriorityTask priority_;
    StartDateTask startDate_;
    DeadlineTask deadline_;

    Container container_ = Container::Horizontal();
};

/*
 *
 */

class Priority : public Component {

public:
    Priority() {
        Add(&container_);                   //Adds a new container
        container_.Add(&task_);             //Adds a task container
        container_.Add(&priority_);         //Adds a priority container
        container_.Add(&status_);           //Adds a status container
        container_.Add(&startDate_);        //Adds a startDate container
        container_.Add(&deadline_);         //Adds a deadline container

        task_.entries = {                   //Defines the entries in the task container
            L"Task 1",                      //Read Task1 Name
            L"Task 2",                      //Read Task2 Name
            L"Task 3",                      //Read Task3 Name
        };
    }

    Element Render() override {
        auto task_win = window(text(L"Task") | center, task_.Render());
        auto priority_win = window(text(L"Priority") | center, priority_.Render());
        auto status_win = window(text(L"Status") | center, status_.Render());
        auto startDate_win = window(text(L"Start-date") | center, startDate_.Render());
        auto deadline_win = window(text(L"Deadline") | center, deadline_.Render());
        return hbox({
            task_win,
            priority_win,
            status_win,
            startDate_win,
            deadline_win,
            });
    }
    std::function<void()> on_enter = []() {};

private:
    Menu task_;
    StatusTask status_;
    PriorityTask priority_;
    StartDateTask startDate_;
    DeadlineTask deadline_;

    Container container_   = Container::Horizontal();
};

/*
 *
 */

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

/*
 *
 */

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


/*
 *
 *
 */



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
             //hbox(text(L"                         Confirm  Cancel")), // Will be changed to buttons later
            }));
    };
};



/*
 *
 */


class Tab : public Component {
public:
    Container main_container = Container::Horizontal();
    Container container = Container::Tab(&menu.selected);

    Menu        menu;
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

std::vector<newTask> gTask[];

/*
 *
 */

int main(int argc, const char* argv[]) {
    auto screen = ScreenInteractive::TerminalOutput();
    Tab tab;
    screen.Loop(&tab);
    return 0;
}