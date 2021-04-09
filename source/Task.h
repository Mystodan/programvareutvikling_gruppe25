#pragma once
#include <string>

class User;
class Category;
class TaskStatus;

struct TaskDB {
	int id = -1;
	std::wstring description;
	int start_time = -1;
	int end_time = -1;
	int category_id = -1; // foreign
	int status_id = -1; // foreign
};

class Task {
public:
	Task(TaskDB task_db) : task_(task_db){}
	int get_id() const;

	std::wstring get_description();
	void set_description(std::wstring description_);

	int get_start_time();
	void set_start_time(int start_time_);

	int get_end_time();
	void set_end_time(int end_time_);

	void add_user(User user);

	/**
	 * \brief removes the junction table entry where
	 * user_id is the provided user's id and task_id is
	 * this task's id
	 * \param user to be removed from being associated with this task
	 */
	void remove_user(User user);

	Category get_category();
	int get_category_id();
	void set_category_id(int category_id_);

	TaskStatus get_status();
	int get_status_id();
	void set_status_id(int status_id_);

	TaskDB get_task() const;

private:
	void update();
	void fetch();

	TaskDB task_{};
};
