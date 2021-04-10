#pragma once
//#include <cassert>
//#include <string>
//#include "Color.h"
//
//class Task;
//struct Color;
//
//struct UserDB {
//	int id = -1;
//	std::wstring first_name;
//	std::wstring last_name;
//	int color_id;  // foreign
//
//};
//
//class User {
//public:
//	User(UserDB user_) : user_(user_) {
//		assert(user_.id != -1);
//	}
//
//	int get_id() const;
//
//	std::wstring get_first_name();
//	void set_first_name(std::wstring first_name_);
//
//	std::wstring get_last_name();
//	void set_last_name(std::wstring last_name_);
//
//	int get_color_id();
//	void set_color_id(int color_id_);
//	Color get_color();
//
//	void add_task(Task task);
//
//	/**
//	 * \brief removes the junction table entry where
//	 * user_id is the user's id and task_id is
//	 * the task's id
//	 * \param task to be removed from being associated with this user
//	 */
//	void remove_task(Task task);
//
//	
//private:
//	void update();
//	void fetch();
//
//	UserDB user_;
//};
