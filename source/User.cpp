#include "User.h"
#include "Task.h"
#include "Color.h"
#include "UsersTasks.h"
#include "Database.h"

#include <sqlite_orm3/sqlite_orm.h>

void User::add_task(Task task) {
	UsersTasksDB users_tasks{ user_.id, task.get_id() };
	Database::add<UsersTasksDB>(users_tasks);
}

void User::remove_task(Task task) {
	using namespace sqlite_orm;
	Database::remove<UsersTasksDB>(where(is_equal(&UserDB::id, user_.id) && is_equal(&TaskDB::id, task.get_id())));
}

int User::get_id() const {
	return user_.id;
}

std::string User::get_first_name() {
	fetch();

	return user_.first_name;
}

void User::set_first_name(std::string first_name_) {
	user_.first_name = first_name_;

	update();
}

std::string User::get_last_name() {
	fetch();

	return user_.last_name;
}

void User::set_last_name(std::string last_name_) {
	user_.last_name = last_name_;

	update();
}

int User::get_color_id() {
	fetch();

	return user_.color_id;
}

void User::set_color_id(int color_id_) {
	user_.color_id = color_id_;

	update();
}

Color User::get_color() {
	fetch();

	return Database::get<Color>(user_.color_id);
}

void User::update() {
	Database::update<UserDB>(user_);
}

void User::fetch() {
	user_ = Database::get<UserDB>(user_.id);
}
