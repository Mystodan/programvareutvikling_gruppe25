#pragma once

#include <ftxui/component/container.hpp>
#include <ftxui/component/checkbox.hpp>

#include "Task.h"

/**
 * \brief Sets up the "Priority" column
 */
class CheckboxColumn : public ftxui::Component {
public:
    CheckboxColumn() {
        Add(&container_);
    }

    void fill_data(const std::vector<std::shared_ptr<Task>>& tasks);
	/**

	 * \brief Adds a task's data to the component,
	 * also sets the callback
	 * \param task Task to be added
	 */
    virtual void add_task(const std::shared_ptr<Task>& task) = 0;
    void clear();

    std::function<void()> on_enter = []() {};
    std::function<void()> on_change = [](){}; // Callback to be called when a state change happens

//private:
	ftxui::Container container_ = ftxui::Container::Vertical();
    std::vector<ftxui::CheckBox*> checkboxes;
};


