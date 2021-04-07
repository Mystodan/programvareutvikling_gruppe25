#pragma once
#include <string>

struct User;
struct Category;
struct TaskStatus;
struct Task {
	/*
	 * DB
	 */
	int id;
	std::string description;
	int start_time;
	int end_time;
	int category_id; // foreign
	int status_id; // foreign

	/*
	 * Non DB
	 */

	void add_user(User user);

	/**
	 * \brief removes the junction table entry where
	 * user_id is the provided user's id and task_id is
	 * this task's id
	 * \param user to be removed from being associated with this task
	 */
	void remove_user(User user);

	Category get_category();
	TaskStatus get_status();
};
