#pragma once

#include <functional>

#include <ftxui/component/container.hpp>
#include <ftxui/component/menu.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include "Category.h"
#include "Tasks.h"
#include "Priority.h"
#include "Completed.h"
#include "RecycleBin.h"
#include "CreateTask.h"
#include "TaskManager.h"
#include "TaskStatus.h"

//using namespace ftxui;

/**
 * \brief "Main" component which holds all the tabs
 */
class SideMenu : public Component {
public:
    Container main_container = Container::Horizontal();
    Container container = Container::Tab(&menu.selected);

    // TODO: Restructure so they are all the same class (except recyclebin and createtask) but with some different properties
    // Makes it easier to add new code for all of them and the layout is the same on all
    Menu        menu;           // Menu tab
    Tasks       td_Tasks;       // Tasks tab
    Priority    td_Priority;    // Priority tab
    Completed   td_Completed;   // Completed tab
    RecycleBin  td_RecycleBin;  // RecycleBin tab
    CreateTask  td_CreateTask;  // CreateTask tab

    SideMenu();

    void RebuildDataEntries();
    bool OnEvent(Event) override;

    Element Render() override;


    std::function<void()> on_change = []() {};

	/*
	 * Sorting
	 */
    enum class SortBy : int {
	    TASKNAME,
        PRIORITY,
    	STATUS,
    	STARTDATE,
    	DEADLINE
    };
    enum class SortOrder : int {
	    ASCENDING = 0,
    	DESCENDING = 1
    };

	SortBy sort_by = SortBy::TASKNAME;
    SortOrder sort_order = SortOrder::ASCENDING;

	std::map<std::string, SortBy> key_map ;

    void sort_tasks(std::vector<std::shared_ptr<Task>>& tasks) const;

};
