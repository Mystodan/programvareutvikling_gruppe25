#pragma once

#include "Task.h"
#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"


using namespace ftxui;

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

    void fill_data(const std::vector<std::shared_ptr<Task>>& tasks);

    std::function<void()> on_enter = []() {};

private:
    Menu status_;
    Container container_ = Container::Vertical();
};
