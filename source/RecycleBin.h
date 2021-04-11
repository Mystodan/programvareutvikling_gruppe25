#pragma once

#include "ftxui/component/container.hpp" // Containers
#include "ftxui/component/menu.hpp"      // Menu 

using namespace ftxui;

// NOT FINISHED!
class RecycleBin : public Component {
public:
    RecycleBin() {
        Add(&container_);
        container_.Add(&task_);

        task_.entries = {               // NB! Example entries!
            L"Task 7",
            L"Task 8",
            L"Task 9",
            L"Task 10",
        };
    }
    Element Render() override {
        auto menu_win = window(text(L"RecycleBin") | center, task_.Render()); // Renders RecycleBin 
        return vbox({ menu_win });
    }

    std::function<void()> on_enter = []() {};

private:
    Menu task_;
    Container container_ = Container::Vertical();
};
