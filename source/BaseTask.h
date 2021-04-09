#pragma once
//#include <ftxui/component/component.hpp>
//#include <ftxui/component/menu.hpp>
//
//
//
//#include "DeadlineTask.h"
//#include "PriorityTask.h"
//#include "StartDateTask.h"
//#include "StatusTask.h"
//#include "TaskManager.h"
//
//// TODO: figure this out and have one vector of these base components in the tab class and then call fill_data from those base components to fill from vec
//class Task;
//
//using namespace ftxui;
//class BaseTask : public Component {
//public:
//    BaseTask() {
//
//        auto tasks = TaskManager::get_all_tasks();
//
//        Add(&container_);                   //Adds a new container
//        container_.Add(&task_);             //Adds a task container
//        container_.Add(&priority_);         //Adds a priority container
//        container_.Add(&status_);           //Adds a status container
//        container_.Add(&startDate_);        //Adds a startDate container
//        container_.Add(&deadline_);         //Adds a deadline container
//
//        priority_.fill_data(tasks);
//        startDate_.fill_data(tasks);
//
//        task_.entries = {                   //Defines the entries in the task container
//            L"Task 1",                      //Read Task1 Name
//            L"Task 2",                      //Read Task2 Name
//            L"Task 3",                      //Read Task3 Name
//        };
//    }
//
//    Element Render() override {
//        auto task_win = window(text(L"Task") | center, task_.Render());
//        auto priority_win = window(text(L"Priority") | center, priority_.Render());
//        auto status_win = window(text(L"Status") | center, status_.Render());
//        auto startDate_win = window(text(L"Start-date") | center, startDate_.Render());
//        auto deadline_win = window(text(L"Deadline") | center, deadline_.Render());
//        return hbox({
//            task_win,
//            priority_win,
//            status_win,
//            startDate_win,
//            deadline_win,
//            });
//
//    }
//    std::function<void()> on_enter = []() {};
//
//private:
//    Menu task_;
//    StatusTask status_;
//    PriorityTask priority_;
//    StartDateTask startDate_;
//    DeadlineTask deadline_;
//
//    Container container_ = Container::Horizontal();
//    void fill_data(const std::vector<Task>& tasks);
//};
