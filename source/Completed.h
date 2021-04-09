#pragma once

/*
 *
 */

#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"

using namespace ftxui;

/*
 *
 */class Completed : public Component {
 public:
     Completed() {
         Add(&container_);
         container_.Add(&task_);

         task_.entries = {
             L"Task 7",
             L"Task 8",
             L"Task 9",
             L"Task 10",
         };
     }
     Element Render() override {
         auto menu_win = window(text(L"Completed") | center, task_.Render()); // Makes window around menu
         return vbox({ menu_win });
     }

     std::function<void()> on_enter = []() {};

 private:
     Menu task_;
     Container container_ = Container::Vertical();
 };