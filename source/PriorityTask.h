#pragma once

/*
 *
 */

#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"
#include "ftxui/component/checkbox.hpp"

using namespace ftxui;

class PriorityTask : public Component {
public:
    PriorityTask() {
        Add(&container_);

        container_.Add(&box_1_);
        container_.Add(&box_2_);
        container_.Add(&box_3_);
        box_1_.label = L" ";
        box_2_.label = L" ";
        box_3_.label = L" ";

    }

    std::function<void()> on_enter = []() {};

private:
    CheckBox box_1_;
    CheckBox box_2_;
    CheckBox box_3_;

    Container container_ = Container::Vertical();
};
