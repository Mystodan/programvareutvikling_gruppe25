#include "Task.h"
#include "Database.h"

/*
 * The getters in the class will all call fetch (see fetch) and then return the property
 * The setters in this calss will all call update (see update) after setting the property for the internal DB object
 */


/**
 * \brief Retrieves task's internal database ID (PK)
 * \return id
 */
int Task::get_id() const {
	return task_.id;
}

/**
 * \brief Retrieves the task's description/name
 * \return task description/name
 * \see Task::fetch()
 */
std::wstring Task::get_description() {
	fetch(); 

	return task_.description;
}

/**
 * \brief Sets the task's description/name
 * \param description_ new description to be set internally
 * \see Task::update()
 */
void Task::set_description(std::wstring description_) {
	task_.description = description_;						   

	update();
}

/**
 * \brief Retrieves the tasks's start time
 * \return start time
 * \see Task::fetch()
 */
int Task::get_start_time() {
	fetch();

	return task_.start_time;
}

/**
 * \brief Sets the tasks's start time
 * \param start_time_ new start time to be set
 * \see Task::update()
 */
void Task::set_start_time(int start_time_) {
	task_.start_time = start_time_;                           

	update();
}

/**
 * \brief Gets the tasks's end time/deadline
 * \return end time/deadline
 * \see Task::fetch()
 */
int Task::get_end_time() {
	fetch();

	return task_.end_time;
}

/**
 * \brief Sets the task's end time/deadline
 * \param end_time_ new end time/deadline to be set
 * \see Task::update()
 */
void Task::set_end_time(int end_time_) {
	task_.end_time = end_time_;						         

	update();
}

//void Task::add_user(User user) {
//	UsersTasksDB users_tasks{ user.get_id(), task_.id };
//	Database::add<UsersTasksDB>(users_tasks);
//}

/**
 * \brief Gets the task's status/progress
 * \return status/progress
 * \see Task::fetch()
 */
int Task::get_status() {
	fetch();

	return task_.status;
}

/**
 * \brief Sets the task's status/progress
 * \param status_ new status/progress to be set
 * \see Task::update()
 */
void Task::set_status(int status_) {
	task_.status = status_;

	update();
}

/**
 * \brief Gets the task's priority
 * \return priority
 * \see Task::fetch()
 */
bool Task::get_priority() {
	fetch();

	return task_.priority;
}

/**
 * \brief Sets the task's priority
 * \param has_priority new priority to be set
 * \see Task::update()
 */
void Task::set_priority(bool has_priority) {
	task_.priority = has_priority;		

	update();
}

/**
 * \brief Checks if the tasks is deleted
 * \return deleted state
 * \see Task::fetch()
 */
bool Task::get_deleted() {
	fetch();

	return task_.deleted;
}

/**
 * \brief Sets the task's deleted state
 * \param deleted new deleted state
 * \see Task::update()
 */
void Task::set_deleted(bool deleted) {
	task_.deleted = deleted;		

	update();
}

/**
 * \brief Retrieves the internal TaskDB object
 * \return internal TaskDB object
 * \see Task::fetch()
 */
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
