#pragma once

/*
 *
 */

#include "ftxui/component/container.hpp"
#include "ftxui/component/checkbox.hpp"
#include "ftxui/component/input.hpp"
#include "ftxui/component/button.hpp"

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
        container.Add(&box);
        container.Add(&input_2);
        container.Add(&input_3);
        container.Add(&input_4);
        container.Add(&confirm_button);
        box.label = L"(X = Priority)";
        confirm_button.label = L"Confirm";

        input_1.on_enter = [this] {
            input.entries.push_back(input_1.content); //Vector? string??
            input_1.content = L" ";
        };
    }
       
private:
    Container container = Container::Vertical();   
    Menu input; //input til string eller char???
    Input input_1;
    Input input_2;
    Input input_3;
    Input input_4;
    CheckBox box;
    Button confirm_button;

    Element Render() override {

        auto input_win = window(text(L"task name"), hbox({input.Render(), }));

        return border(vbox({
             hbox({text(L"Insert name of task: "), input_1.Render()}),
             hbox({text(L"Choose priority of task: "), box.Render()}),
             hbox({text(L"Insert status for task (0-100%): "), input_2.Render()}),
             hbox({text(L"Set start-date for task (dd.mm.yy): "), input_3.Render()}),
             hbox({text(L"Set deadline for task (dd.mm.yy): "), input_4.Render()}),
             hbox(confirm_button.Render()),
             vbox({input_win | size(WIDTH, EQUAL, 60), }),
            })); 
    };
};
