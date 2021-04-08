#pragma once
#include <string>

struct TaskStatusDB {
	int id;
	std::string description;
};

class TaskStatus {
public:
	TaskStatus(TaskStatusDB tasks_status) : tasks_status_(tasks_status){}
	int get_id() const;

	std::string get_description();
	void set_description(std::string description_);
private:
	void update();
	void fetch();

	TaskStatusDB tasks_status_;
};

