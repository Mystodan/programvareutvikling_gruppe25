#pragma once

#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"

/**
* \Forward declaration of task
*/
class Task;

/**
* \brief StatusTask includes: filling, adding & clearing status data
*/
class StatusTask : public ftxui::Component {
public:
    StatusTask() {
        Add(&container_);
        container_.Add(&status_);

    }
    void fill_data(const std::vector<std::shared_ptr<Task>>& tasks);
    void add_task(const std::shared_ptr<Task>& task);
    void clear();

    std::function<void()> on_enter = []() {};

private:
    ftxui::Menu status_;
    ftxui::Container container_ = ftxui::Container::Vertical();
};
