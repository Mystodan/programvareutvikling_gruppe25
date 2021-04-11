#include "Task.h"
#include "User.h"
#include "Database.h"

int Task::get_id() const {										//Gets and returns task ID
	return task_.id;
}

std::wstring Task::get_description() {							//Gets and returns description
	return task_.description;
}

void Task::set_description(std::wstring description_) {		   //Sets task description to description_
	task_.description = description_;						   

	update();												   //Calls update function
}

int Task::get_start_time() {									   //Gets and returns start time
	fetch();

	return task_.start_time;
}

void Task::set_start_time(int start_time_) {					  //Sets task start time to start_time
	task_.start_time = start_time_;                           

	update();												  //Calls update function
}

int Task::get_end_time() {									  //Gets and returns end time
	fetch();

	return task_.end_time;
}

void Task::set_end_time(int end_time_) {                     //Sets task end time to end_time_ 
	task_.end_time = end_time_;						         

	update();												 //Calls update function
}

//void Task::add_user(User user) {
//	UsersTasksDB users_tasks{ user.get_id(), task_.id };
//	Database::add<UsersTasksDB>(users_tasks);
//}

int Task::get_status() {										//Gets and returns task status
	fetch();

	return task_.status;
}

void Task::set_status(int status_) {							//Sets task status to status_
	task_.status = status_;

	update();											    //Calls update function
}

bool Task::get_priority() {									//Gets and returns task priority, bool
	fetch();

	return task_.priority;
}

void Task::set_priority(bool has_priority) {				    //Uses the bool above, if task has priority then returns it
	task_.priority = has_priority;		

	update();												//Calls update function
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

void Task::update() {
	Database::update<TaskDB>(task_);
}

void Task::fetch() {
	task_ = Database::get<TaskDB>(task_.id);
}
