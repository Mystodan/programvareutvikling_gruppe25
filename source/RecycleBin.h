#pragma once

#include "AllTask.h"
#include "DeleteTask.h"
#include "ftxui/component/container.hpp" // Containers
#include "ftxui/component/menu.hpp"      // Menu 
#include "ftxui/component/button.hpp"    // Button

/**
 * \brief Modal dialog for confirming user action
 */
class ConfirmationDialog : public ftxui::Component {
public:
	ConfirmationDialog();

	ftxui::Element Render() override;

	ftxui::Container container = ftxui::Container::Horizontal();

	ftxui::Button yes_button;
	ftxui::Button no_button;

	std::function<void()> on_yes;
	std::function<void()> on_no;
};

/**
 * \brief RecycleBin that holds all tasks marked as deleted
 */
class RecycleBin : public ftxui::Component {
public:
	RecycleBin();

	ftxui::Element Render() override;

	// Gets the updated data and rebuilds the program
	void rebuild_data(const std::vector<std::shared_ptr<Task>>& tasks,
		std::function<bool(const std::shared_ptr<Task>&)> predicate, std::function<void()> on_change);

	std::function<void()> on_change = []() {};

	bool is_empty() const;

private:
	ftxui::Menu tasks_;          // Tasks column
	DeleteTask deleted_;    // Delete column 
	ConfirmationDialog confirmation_dialog_;

	ftxui::Button delete_button_;

	ftxui::Container container_ = ftxui::Container::Tab(nullptr);
	ftxui::Container content_ = ftxui::Container::Vertical();
	ftxui::Container row_container_ = ftxui::Container::Horizontal();
	ftxui::Container subcontainer_ = ftxui::Container::Vertical();

	std::vector<std::shared_ptr<Task>> tasks_vec{};
};

