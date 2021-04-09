#pragma once
#include <cassert>
#include <memory>
#include <vector>

class Task;
class User;

struct UsersTasksDB {
	int user_id = -1; // foreign
	int task_id = -1; // foreign
};

class UsersTasks {
public:
	UsersTasks() = default;
	UsersTasks(UsersTasksDB users_tasks) : users_tasks_(users_tasks) {
		assert(users_tasks.user_id != -1);
		assert(users_tasks.task_id != -1);
	}
	Task get_task();
	User get_user();
private:
	UsersTasksDB users_tasks_{};
};

struct UserTasksManager {
	static std::vector<User> get_users_by_task(Task task);
	static std::vector<Task> get_tasks_by_user(User user);
	static std::vector<std::shared_ptr<User>> get_all_users();
	static std::vector<std::shared_ptr<Task>> get_all_tasks();
};

