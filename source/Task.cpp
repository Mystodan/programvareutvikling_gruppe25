#include "Task.h"
#include "User.h"
#include "Database.h"

/*
 * The getters in the class will all call fetch (see fetch) and then return the property
 * The setters in this calss will all call update (see update) after setting the property for the internal DB object
 */

int Task::get_id() const {
	return task_.id;
}

std::wstring Task::get_description() {
	fetch(); 

	return task_.description;
}

void Task::set_description(std::wstring description_) {
	task_.description = description_;						   

	update();
}

int Task::get_start_time() {
	fetch();

	return task_.start_time;
}

void Task::set_start_time(int start_time_) {
	task_.start_time = start_time_;                           

	update();
}

int Task::get_end_time() {
	fetch();

	return task_.end_time;
}

void Task::set_end_time(int end_time_) {
	task_.end_time = end_time_;						         

	update();
}

//void Task::add_user(User user) {
//	UsersTasksDB users_tasks{ user.get_id(), task_.id };
//	Database::add<UsersTasksDB>(users_tasks);
//}

int Task::get_status() {
	fetch();

	return task_.status;
}

void Task::set_status(int status_) {
	task_.status = status_;

	update();
}

bool Task::get_priority() {
	fetch();

	return task_.priority;
}

void Task::set_priority(bool has_priority) {
	task_.priority = has_priority;		

	update();
}

bool Task::get_deleted() {
	fetch();

	return task_.deleted;
}

void Task::set_deleted(bool deleted) {
	task_.deleted = deleted;		

	update();
}

//void Task::remove_user(User user) {
//	using namespace sqlite_orm;
//	Database::remove<UsersTasksDB>(where(is_equal(&UserDB::id, user.get_id()) && where(is_equal(&TaskDB::id, task_.id))));
//}



//Category Task::get_category() {
//	fetch();
//
//	return Database::get<CategoryDB>(task_.category_id);
//}
//
//int Task::get_category_id() {
//	fetch();
//
//	return task_.category_id;
//}
//
//void Task::set_category_id(int category_id_) {
//	task_.category_id = category_id_;
//
//	update();
//}
//
//TaskStatus Task::get_status() {
//	fetch();
//
//	return Database::get<TaskStatusDB>(task_.status_id);
//}
//
//int Task::get_status_id() {
//	fetch();
//
//	return task_.status_id;
//}
//
//void Task::set_status_id(int status_id_) {
//	task_.status_id = status_id_;
//
//	update();
//}

TaskDB Task::get_task() const {
	return task_;
}

/**
 * \brief Updates the database with the internal task_ object data
 */
void Task::update() {
	Database::update<TaskDB>(task_);
}


/**
 * \brief Fetches new data for our internal task_ object from the database
 */
void Task::fetch() {
	task_ = Database::get<TaskDB>(task_.id);
}
