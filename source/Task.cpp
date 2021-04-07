#include "Task.h"
#include "User.h"
#include "Database.h"

void Task::add_user(User user) {
	UsersTasks users_tasks{ user.id, id };
	Database::add<UsersTasks>(users_tasks);
}

void Task::remove_user(User user) {
	using namespace sqlite_orm;
	Database::remove<UsersTasks>(where(is_equal(&User::id, user.id) && where(is_equal(&Task::id, id))));
}

Category Task::get_category() {
	return Database::get<Category>(category_id);
}

TaskStatus Task::get_status() {
	return Database::get<TaskStatus>(status_id);
}
