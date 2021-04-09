#pragma once

#include <ftxui/component/container.hpp>
#include <ftxui/component/checkbox.hpp>

#include "Task.h"

class PriorityTask : public ftxui::Component {
public:
    PriorityTask() {
        Add(&container_);
    }

    void fill_data(const std::vector<std::shared_ptr<Task>>& tasks);

    std::function<void()> on_enter = []() {};

private:
    ftxui::Container container_ = ftxui::Container::Vertical();
};


