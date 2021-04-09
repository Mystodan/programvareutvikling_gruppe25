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

        confirm_button.on_click = [&]() {
            // TODO: Check if empty and give error/warning in the window below
            std::wstring description = input_1.content;
            int priority = static_cast<int>(box.state);
            int status = stoi(input_2.content);
            int start_date = 0; // replace with input_3 content
            int end_date = 100; // replace with input_4 content

            // 1 is priority?? DB doesn't match wireframe
            TaskDB task{ -1, description, start_date, end_date, 1, status };

            TaskManager::add_task(task);

            on_change();

        	// Clear data
            input_1.content.clear();
            input_2.content.clear();
            input_3.content.clear();
            input_4.content.clear();
        };
        input_1.on_enter = [this] {
            input.entries.push_back(input_1.content); //Vector? string??
            input_1.content = L" ";
        };
    }
    std::function<void()> on_change = [](){};
       
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
             hbox({confirm_button.Render()}),
             vbox({input_win | size(WIDTH, EQUAL, 60), }),
            })); 
    };
};
