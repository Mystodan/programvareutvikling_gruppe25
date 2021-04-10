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
			auto is_number = [](const std::wstring& s) {
				return !s.empty() && std::find_if(s.begin(),
					s.end(), [](wchar_t c) { return !std::isdigit(c); }) == s.end();
			};

			output_window_.entries.clear();

            // This is to be filled in
            TaskDB task;

            bool valid_data = true;

            if (status_input_.content.empty()) {
                output_window_.entries.emplace_back(L"The task cannot have an empty status");
                valid_data = false;
            }

            if (!is_number(status_input_.content)) {
                output_window_.entries.emplace_back(L"The status must be a number");
                valid_data = false;
            }

            // TODO: Check if empty and give error/warning in the Menu input below
            std::wstring description = description_input_.content;
			if (description.empty()) {
                output_window_.entries.emplace_back(L"The task needs to have a name");
                valid_data = false;
			}

            std::wstring start_time_str = start_time_input_.content;
            if (start_time_str.empty()) {
                output_window_.entries.emplace_back(L"The task needs to have a start time");
                valid_data = false;
            }

        	if (valid_data) {
				task.description = description;

				int start_time = 0; // replace with end_time_ content TODO: convert string dd.mm.yy to unix time
				int end_time = 100; // replace with start_time_ content TODO: convert string dd.mm.yy to unix time

				task.start_time = start_time;
				task.end_time = end_time;
				task.priority = static_cast<int>(priority_box.state);

				task.status = stoi(status_input_.content);

				TaskManager::add_task(task);

				on_change();

				// Clear data
				description_input_.content.clear();
				status_input_.content.clear();
				start_time_input_.content.clear();
				end_time_input_.content.clear();
        	}
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

        auto input_win = window(text(L"Output"), hbox({output_window_.Render(), }));

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
