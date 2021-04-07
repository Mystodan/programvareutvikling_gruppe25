#pragma once
#include <vector>

struct Task;
struct User;

struct UsersTasks {
	/*
	 * DB
	 */
	int user_id; // foreign
	int task_id; // foreign

	/*
	 * Non DB
	 */

	Task get_task();
	User get_user();
};

struct UserTasksManager {
	static std::vector<User> get_users_by_task(Task task);
	static std::vector<Task> get_tasks_by_user(User user);
};

