#pragma once

#include "Task.h"
#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"


using namespace ftxui;

/**
 * \brief Sets up the "Priority" column
 */
class DeadlineTask : public Component {
public:
    DeadlineTask() {
        Add(&container_);
        container_.Add(&status_);
    }

    void fill_data(const std::vector<std::shared_ptr<Task>>& tasks);
    void add_task(const std::shared_ptr<Task>& task);
    void clear();

    std::function<void()> on_enter = []() {};

private:
    Menu status_;
    Container container_ = Container::Vertical();
};
