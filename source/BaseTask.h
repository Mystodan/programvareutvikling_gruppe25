#pragma once
#include <ftxui/component/menu.hpp> // Menu
#include "ftxui/component/container.hpp"
#include "ftxui/component/input.hpp" 

#include "DeadlineTask.h" 
#include "PriorityTask.h"
#include "StartDateTask.h"
#include "StatusTask.h"
#include "TaskManager.h"

// TODO: figure this out and have one vector of these base components in the SideMenu class and then call fill_data from those base components to fill from vec
class Task;

class BaseTask : public Component {
public:
    BaseTask() {
        Add(&container_);                   // Adds a new container to BaseTask
        container_.Add(&task_);             // Adds task_ to the container
        container_.Add(&priority_);         // Adds priority_ to the container
        container_.Add(&status_);           // Adds status to_ the container
        container_.Add(&startDate_);        // Adds startDate_ to the container
        container_.Add(&deadline_);         // Adds deadline_ to the container
    }

    // Gets the updated data and rebuilds the program
    void rebuild_data(const std::vector<std::shared_ptr<Task>>& tasks,
                      std::function<bool(const std::shared_ptr<Task>&)> predicate, std::function<void()> on_change);

    // Renders everything in BaseTask to the user
    Element Render() override;

    std::function<void()> on_change = []() {};

    // Bool for is_number 
   // bool is_number(const std::wstring& s) {
     //   return !s.empty() && std::find_if(s.begin();
       // s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    //}

private:
    Menu task_;
    Menu output_window_;
    StatusTask status_;                             
    PriorityTask priority_;               
    StartDateTask startDate_;                     
    DeadlineTask deadline_;                        
    Container container_ = Container::Horizontal(); // Adds container variable
};
