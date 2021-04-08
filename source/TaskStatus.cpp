#include "TaskStatus.h"

#include "Database.h"

int TaskStatus::get_id() const {
	return tasks_status_.id;
}

std::string TaskStatus::get_description() {
	fetch();

	return tasks_status_.description;
}

void TaskStatus::set_description(std::string description_) {
	tasks_status_.description = description_;

	update();
}

void TaskStatus::update() {
	Database::update<TaskStatusDB>(tasks_status_);
}

void TaskStatus::fetch() {
	tasks_status_ = Database::get<TaskStatusDB>(tasks_status_.id);
}
