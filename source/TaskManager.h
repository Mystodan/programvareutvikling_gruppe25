#pragma once
#include <memory>
#include <vector>


#include "database.h"
#include "User.h"

class TaskManager {
public:
	std::vector<std::shared_ptr<User>> get_all_users();
	std::vector<std::shared_ptr<Task>> get_all_tasks();

	void add_task(Task task);
	Task get_task(int task_id);
};
