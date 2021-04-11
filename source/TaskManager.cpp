#include "TaskManager.h"
#include "Task.h"
#include "User.h"
#include "Database.h"

using namespace sqlite_orm;

//std::vector<std::shared_ptr<User>> TaskManager::get_all_users() {
//	auto users_db = Database::get_db().get_all<UserDB>();
//	std::vector<std::shared_ptr<User>> users{};
//	users.reserve(users_db.size());
//	for (auto user_db : users_db) {
//		users.emplace_back(std::make_shared<User>(user_db));
//	}
//	return users;
//}

/**
 * \brief Will fetch all the tasks in the database
 * \return all tasks as a shared_ptr of type Task
 */
std::vector<std::shared_ptr<Task>> TaskManager::get_all_tasks() {
	auto tasks_db = Database::get_db().get_all<TaskDB>();
	std::vector<std::shared_ptr<Task>> tasks{};
	tasks.reserve(tasks_db.size());
	for (auto task_db : tasks_db) {
		tasks.emplace_back(std::make_shared<Task>(task_db));
	}
	return tasks;
}

/**
 * \brief Adds a new task to the database from a task object
 * \param task Task to be added to the database
 */
void TaskManager::add_task(Task task) {
	Database::add<TaskDB>(task.get_task());
}

/**
 * \brief Gets a task from the database based on id
 * \param task_id id of the task object we want
 * \return the task object
 */
Task TaskManager::get_task(int task_id) {
	return Database::get<TaskDB>(task_id);
}
