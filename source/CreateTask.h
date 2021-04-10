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
        container.Add(&description_input_);
        container.Add(&priority_box);
        container.Add(&status_input_);
        container.Add(&start_time_input_);
        container.Add(&end_time_input_);
        container.Add(&confirm_button);

        priority_box.label = L"(X = Priority)";
        confirm_button.label = L"Confirm";

        confirm_button.on_click = [&]() {
            // This is to be filled in
            TaskDB task;

            int priority = static_cast<int>(priority_box.state);
            if (status_input_.content.empty()) {
                output_window_.entries.emplace_back(L"The task cannot have an empty status");
                return;
            }

            task.status = stoi(status_input_.content);

            // TODO: Check if empty and give error/warning in the Menu input below
            std::wstring description = description_input_.content;
			if (description.empty()) {
                output_window_.entries.emplace_back(L"The task needs to have a name");
                return;
			}
            task.description = description;

            int start_time = 0; // replace with input_3 content TODO: convert string dd.mm.yy to unix time
            task.start_time = start_time;

            std::wstring start_time_str = start_time_input_.content;
            if (start_time_str.empty()) {
                output_window_.entries.emplace_back(L"The task needs to have a start time");
                return;
            }

            int end_time = 100; // replace with input_4 content TODO: convert string dd.mm.yy to unix time
            task.end_time = end_time;

            // 1 is priority?? DB doesn't match wireframe, need to change
            //TaskDB task{ -1, description, start_date, end_date, 1, status };

            TaskManager::add_task(task);

            on_change();

        	// Clear data
            description_input_.content.clear();
            status_input_.content.clear();
            start_time_input_.content.clear();
            end_time_input_.content.clear();
        };
    }
    std::function<void()> on_change = [](){};
       
private:
    Container container = Container::Vertical();   
    Menu output_window_;
    Input description_input_;
    Input status_input_;
    Input start_time_input_;
    Input end_time_input_;
    CheckBox priority_box;
    Button confirm_button;

    Element Render() override {

        auto input_win = window(text(L"task name"), hbox({output_window_.Render(), }));

        return border(vbox({
             hbox({text(L"Insert name of task: "), description_input_.Render()}),
             hbox({text(L"Choose priority of task: "), priority_box.Render()}),
             hbox({text(L"Insert status for task (0-100%): "), status_input_.Render()}),
             hbox({text(L"Set start-date for task (dd.mm.yy): "), start_time_input_.Render()}),
             hbox({text(L"Set deadline for task (dd.mm.yy): "), end_time_input_.Render()}),
             hbox({confirm_button.Render()}),
             vbox({input_win | size(WIDTH, EQUAL, 60), }),
            })); 
    };
};
