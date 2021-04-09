#pragma once

/*
 *
 */

#include "ftxui/component/container.hpp"
#include "ftxui/component/checkbox.hpp"
#include "EmptyCheckBox.h"
#include "Category.h"
#include "Task.h"

using namespace ftxui;

class PriorityTask : public Component {
public:
    PriorityTask() {
        Add(&container_);
    }

    void fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
        for (const auto& task : tasks) {
            auto* checkbox = new EmptyCheckBox();

            checkbox->state = task->get_category().get_priority();

            checkbox->on_change = [=]() {
                task->get_category().set_priority(checkbox->state);
            };

            container_.Add(checkbox);
        }
    }

    std::function<void()> on_enter = []() {};

private:
    Container container_ = Container::Vertical();
};


