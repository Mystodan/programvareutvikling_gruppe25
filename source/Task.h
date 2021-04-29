#pragma once
#include <string>
#include <utility>

class User;
class TaskStatus;

/**
 * \brief structure for internal Database Data
 */
struct TaskDB {
	int id = -1;
	std::wstring description;
	int start_time = -1;
	int end_time = -1;
	int status = -1;
	int priority = 0; // Acts like boolean
	int deleted = 0; // Acts like boolean
};

class Task {
public:
	Task(TaskDB task_db) : task_(std::move(task_db)){}
	int get_id() const;

	std::wstring get_description();
	void set_description(std::wstring description_);

	int get_start_time();
	void set_start_time(int start_time_);

	int get_end_time();
	void set_end_time(int end_time_);

	int get_status();
	void set_status(int status_);

	bool get_priority();
	void set_priority(bool has_priority);

	bool get_deleted();
	void set_deleted(bool deleted);

	TaskDB get_task() const;

private:
	void update();
	void fetch();

	TaskDB task_{};
};
