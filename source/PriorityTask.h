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
    void add_task(const std::shared_ptr<Task>& task);
    void clear();
    //ftxui::Element Render() override;

    std::function<void()> on_enter = []() {};
    std::function<void()> on_change = [](){};

private:
	ftxui::Container container_ = ftxui::Container::Vertical();
    std::vector<ftxui::CheckBox*> checkboxes;
};


