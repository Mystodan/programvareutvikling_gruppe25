#include "User.h"
#include "Task.h"
#include "Color.h"
#include "UsersTasks.h"
#include "Database.h"

#include <sqlite_orm3/sqlite_orm.h>

void User::add_task(Task task) {
	UsersTasks users_tasks{ id, task.id };
	Database::add<UsersTasks>(users_tasks);
}

void User::remove_task(Task task) {
	using namespace sqlite_orm;
	Database::remove<UsersTasks>(where(is_equal(&User::id, id) && is_equal(&Task::id, task.id)));
}

Color User::get_color() {
	return Database::get<Color>(color_id);
}
