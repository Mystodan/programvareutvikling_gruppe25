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

    void rebuild_data(const std::vector<std::shared_ptr<Task>>& tasks,
                      std::function<bool(const std::shared_ptr<Task>&)> predicate, std::function<void()> on_change);

    Element Render() override;
    std::function<void()> on_enter = []() {};

private:
    Menu task_;
    StatusTask status_;
    PriorityTask priority_;
    StartDateTask startDate_;
    DeadlineTask deadline_;

    Container container_ = Container::Horizontal();
};
