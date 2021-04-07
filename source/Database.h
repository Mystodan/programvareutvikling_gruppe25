#pragma once
#include <sqlite_orm3/sqlite_orm.h>
#include <iostream>

#include "Category.h"
#include "Color.h"
#include "Task.h"
#include "TaskStatus.h"
#include "User.h"
#include "UsersTasks.h"

namespace Database {

	inline auto get_db() {
		using namespace sqlite_orm;

		// Only initialize and sync once
		static auto storage = []() {
			auto storage = make_storage("new_test.sqlite",
				make_table("users",
					make_column("id", &User::id, autoincrement(), primary_key()),
					make_column("first_name", &User::first_name),
					make_column("last_name", &User::last_name),
					make_column("color_id", &User::color_id),
					foreign_key(&User::color_id).references(&Color::id)),
				make_table("tasks",
					make_column("id", &Task::id, autoincrement(), primary_key()),
					make_column("description", &Task::description), // allow null
					make_column("start_time", &Task::start_time, default_value(0)),
					make_column("end_time", &Task::end_time, default_value(0)),
					make_column("category_id", &Task::category_id),
					foreign_key(&Task::category_id).references(&Category::id),
					make_column("status_id", &Task::status_id),
					foreign_key(&Task::status_id).references(&TaskStatus::id)),
				make_table("users_tasks", // Junction table
					make_column("user_id", &UsersTasks::user_id),
					foreign_key(&UsersTasks::user_id).references(&User::id),
					make_column("task_id", &UsersTasks::task_id),
					foreign_key(&UsersTasks::task_id).references(&Task::id)),
				make_table("color",
					make_column("id", &Color::id, autoincrement(), primary_key()),
					make_column("hex_color", &Color::hex_value)),
				make_table("categories",
					make_column("id", &Category::id, autoincrement(), primary_key()),
					make_column("description", &Category::description),
					make_column("priority", &Category::priority),
					make_column("color_id", &Category::color_id),
					foreign_key(&Category::color_id).references(&Color::id)),
				make_table("task_statuses",
					make_column("id", &TaskStatus::id, autoincrement(), primary_key()),
					make_column("description", &TaskStatus::description))
			);
			try {
				storage.sync_schema(); // Sync schema and ignore tables that might not exist in the schema defined here
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << "\n";
			}

			return storage;
		}();

		return storage;
	}

	/**
	 * \brief adds the object to the database
	 * \param object to be added to the database
	 * \return created id of the object
	 */
	template <typename T>
	int add(T object) {
		return get_db().insert(object);
	}

	/**
	 * \brief removes the object to the database
	 * \param object to be added to the database
	 * \return created id of the object
	 */
	template <typename T>
	void remove(T object) {
		return get_db().remove(object);
	}

    template<class T, class... Args>
	void remove(Args... args) {
		return get_db().remove_all<T>(args...);
	}

	/**
	 * \brief updates the object data in the database
	 * \param object to be updated with new data
	 */
	template <typename T>
	void update(T object) {
		try {
			get_db().update(object);
		}
		catch (std::system_error& e) {
			std::cerr << e.what() << "\n";
		}
		catch (...) {
			std::cerr << "unknown exception\n";
		}
	}

	/**
	 * \brief fetches object from the database
	 * \param id of the object in the database
	 * \return object data from the database or a object with id -1 if failed
	 */
	template <typename T>
	T get(int id) {
		try {
			auto user = get_db().get<T>(id);
			return user;
		}
		catch (std::system_error& e) {
			std::cerr << e.what() << "\n";
		}
		catch (...) {
			std::cerr << "unknown exception\n";
		}
		return T{ -1 };
	}

	/**
	 * \brief Inserts default data needed for the DB
	 * This is not really a good function to do on every startup, only needs to be done once
	 */
	extern void insert_default_data();
}
