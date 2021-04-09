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

std::vector<std::shared_ptr<User>> UserTasksManager::get_all_users() {
	using namespace sqlite_orm;
	auto users_db = Database::get_db().get_all<UserDB>();
	std::vector<std::shared_ptr<User>> users{};
	users.reserve(users_db.size());
	for (auto user_db : users_db) {
		users.emplace_back(std::make_shared<User>(user_db));
	}
	return users;
}

std::vector<std::shared_ptr<Task>> UserTasksManager::get_all_tasks() {
	using namespace sqlite_orm;
	auto tasks_db = Database::get_db().get_all<TaskDB>();
	std::vector<std::shared_ptr<Task>> tasks{};
	tasks.reserve(tasks_db.size());
	for (auto task_db : tasks_db) {
		tasks.emplace_back(std::make_shared<Task>(task_db));
	}
	return tasks;
}
	
		 
