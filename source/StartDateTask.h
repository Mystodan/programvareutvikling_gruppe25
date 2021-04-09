#pragma once

#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"

using namespace ftxui;

class StartDateTask : public Component {
public:
    StartDateTask() {
        Add(&container_);
        container_.Add(&status_);
    }
    void fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
        status_.entries.clear();
        for (const auto& task : tasks) {
            status_.entries.push_back(std::to_wstring(task->get_start_time()));
        }
    }
    std::function<void()> on_enter = []() {};

private:
    Menu status_;
    Container container_ = Container::Vertical();
};
