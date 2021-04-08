#include "UsersTasks.h"

#include "Database.h"

#include "Task.h"
#include "User.h"


Task UsersTasks::get_task() {
	return Database::get<Task>(task_id);
}

User UsersTasks::get_user() {
	return Database::get<User>(user_id);
}

std::vector<User> UserTasksManager::get_users_by_task(Task task) {
	using namespace sqlite_orm;
	std::vector<User> users{};

	// TODO: figure out and convert to use JOIN directly here to directly return the correct data entries
	auto entries = Database::get_db().get_all<UsersTasks>(where(is_equal(&Task::id, task.id)));
	for (auto& entry : entries) {
		users.push_back(entry.get_user());
	}

	return users;
}

std::vector<Task> UserTasksManager::get_tasks_by_user(User user) {
	using namespace sqlite_orm;
	std::vector<Task> tasks{};

	// TODO: figure out and convert to use JOIN directly here to directly return the correct data entries
	auto entries = Database::get_db().get_all<UsersTasks>(where(is_equal(&User::id, user.id)));
	for (auto& entry : entries) {
		tasks.push_back(entry.get_task());
	}
	return tasks;
}
	
		 
