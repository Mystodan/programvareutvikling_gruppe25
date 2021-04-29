#include "TaskManager.h"
#include "Task.h"
#include "Database.h"

using namespace sqlite_orm;

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
 * \brief Deletes a task from the database with a task object
 * \param task Task to be delted to the database
 */
void TaskManager::delete_task(Task task) {
	Database::remove<TaskDB>(task.get_task());
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
