#include "UsersTasks.h"

#include "Database.h"

#include "Task.h"
#include "User.h"


Task UsersTasks::get_task() {
	return Database::get<TaskDB>(users_tasks_.task_id);
}

User UsersTasks::get_user() {
	return Database::get<UserDB>(users_tasks_.user_id);
}

std::vector<User> UserTasksManager::get_users_by_task(Task task) {
	using namespace sqlite_orm;
	std::vector<User> users{};

	// TODO: figure out and convert to use JOIN directly here to directly return the correct data entries
	auto entries = Database::get_db().get_all<UsersTasksDB>(where(is_equal(&TaskDB::id, task.get_id())));
	users.reserve(entries.size());
	for (auto& entry : entries) {
		users.emplace_back(UserDB{ entry.user_id });
	}

	return users;
}

std::vector<Task> UserTasksManager::get_tasks_by_user(User user) {
	using namespace sqlite_orm;
	std::vector<Task> tasks{};

	// TODO: figure out and convert to use JOIN directly here to directly return the correct data entries
	auto entries = Database::get_db().get_all<UsersTasksDB>(where(is_equal(&UserDB::id, user.get_id())));
	tasks.reserve(entries.size());
	for (auto& entry : entries) {
		tasks.emplace_back(TaskDB{ entry.task_id });
	}
	return tasks;
}

