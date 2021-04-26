#pragma once
#include <ftxui/component/container.hpp>
#include <ftxui/component/checkbox.hpp>
//#include <ftxui/component/input.hpp>
#include "CustomInput.h"

#include "Task.h"

/**
 * \brief Sets up the "Priority" column
 */
class InputColumn : public ftxui::Component {
public:
    InputColumn() {
        Add(&container_);
    }

    void fill_data(const std::vector<std::shared_ptr<Task>>& tasks);

    void clear();



	/**
	 * \brief Adds a task's data to the component,
	 * also sets the callback
	 * \param task Task to be added
	 */
    virtual void add_task(const std::shared_ptr<Task>& task) = 0;
    std::function<void()> on_change = [](){}; // Callback to be called when a state change happens

	ftxui::Container container_ = ftxui::Container::Vertical();
    std::vector<ftxui::CustomInput*> inputboxes;
};


