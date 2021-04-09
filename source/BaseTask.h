#pragma once
#include <ftxui/component/component.hpp>
#include <ftxui/component/menu.hpp>

#include "DeadlineTask.h"
#include "PriorityTask.h"
#include "StartDateTask.h"
#include "StatusTask.h"
#include "TaskManager.h"

// TODO: figure this out and have one vector of these base components in the tab class and then call fill_data from those base components to fill from vec
class Task;

using namespace ftxui;
class BaseTask : public Component {
public:
    BaseTask() {
        Add(&container_);                   //Adds a new container
        container_.Add(&task_);             //Adds a task container
        container_.Add(&priority_);         //Adds a priority container
        container_.Add(&status_);           //Adds a status container
        container_.Add(&startDate_);        //Adds a startDate container
        container_.Add(&deadline_);         //Adds a deadline container
    }

	void fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
        for (auto& task : tasks) {
            task_.entries.push_back(task->get_description());
        }

        priority_.fill_data(tasks);
        startDate_.fill_data(tasks);
        deadline_.fill_data(tasks);
        status_.fill_data(tasks);
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
