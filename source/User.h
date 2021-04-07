#pragma once
#include <string>

struct Task;
struct Color;

struct User {
	/*
	 * DB
	 */
	int id;
	std::string first_name;
	std::string last_name;
	int color_id;  // foreign

	/*
	 * Non DB
	 */


	void add_task(Task task);

	/**
	 * \brief removes the junction table entry where
	 * user_id is the user's id and task_id is
	 * the task's id
	 * \param task to be removed from being associated with this user
	 */
	void remove_task(Task task);

	Color get_color();
};
