#pragma once

/*
 *
 */

#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"

using namespace ftxui;

class StatusTask : public Component {
public:
    StatusTask() {
        Add(&container_);
        container_.Add(&status_);


        status_.entries = {
               L"75%",                  //Read Task1 status
               L"50%",
               L"0%",
        };
    }
    std::function<void()> on_enter = []() {};

private:
    Menu status_;
    Container container_ = Container::Vertical();
};
