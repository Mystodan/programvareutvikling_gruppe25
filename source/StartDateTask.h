#pragma once

#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"
#include <ctime>
#include <string>

class Task;

class StartDateTask : public ftxui::Component {
public:
    StartDateTask() {
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
