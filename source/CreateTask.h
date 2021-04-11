#pragma once

#include <ftxui/component/menu.hpp>

#include "ftxui/component/container.hpp"
#include "ftxui/component/checkbox.hpp"
#include "ftxui/component/input.hpp"
#include "ftxui/component/button.hpp"

using namespace ftxui;

/**
* Creates new task, which gets added to database
*/
class CreateTask : public Component {
public:
	CreateTask();
    std::function<void()> on_change = [](){};
       
private:
    Container container = Container::Vertical(); // Relevant features from library are added
    Menu output_window_;                         // to be used to create new tasks
    Input description_input_;  
    Input status_input_;
    Input start_time_input_;
    Input end_time_input_;
    CheckBox priority_box;
    Button confirm_button;

	Element Render() override;;
};
