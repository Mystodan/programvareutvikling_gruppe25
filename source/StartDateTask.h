#pragma once

/*
 *
 */

#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"

using namespace ftxui;

class StartDateTask : public Component {
public:
    StartDateTask() {
        Add(&container_);
        container_.Add(&status_);

        status_.entries = {
               L"01.04.21",             //Read Task1 StartDate
               L"01.04.21",
               L"01.04.21",
               L"02.04.21",
        };
    }
    std::function<void()> on_enter = []() {};

private:
    Menu status_;
    Container container_ = Container::Vertical();
};
