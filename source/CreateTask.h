#pragma once

/*
 *
 */

#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"
#include "ftxui/component/checkbox.hpp"
#include "ftxui/component/input.hpp"

using namespace ftxui;

/*
 *
 *
 */

class CreateTask : public Component {
public:
    CreateTask() {
        Add(&container);
        container.Add(&input_1);
        container.Add(&box_2);
        container.Add(&input_3);
        container.Add(&input_4);
        container.Add(&input_5);
        box_2.label = L"(X = Priority)";
    }

    std::function<void()> on_enter = []() {};

private:
    Container container = Container::Vertical();
    Input input_1;
    CheckBox box_2;
    Input input_3;
    Input input_4;
    Input input_5;

    Element Render() override {

        return border(vbox({
             hbox({text(L"Insert name of task: "), input_1.Render()}),
             hbox({text(L"Choose priority of task: "), box_2.Render()}),
             hbox({text(L"Insert status for task (0-100%): "), input_3.Render()}),
             hbox({text(L"Set start-date for task (dd.mm.yy): "), input_4.Render()}),
             hbox({text(L"Set deadline for task (dd.mm.yy): "), input_5.Render()}),
             //hbox(text(L"                         Confirm  Cancel")), // Will be changed to buttons later
            }));
    };
};