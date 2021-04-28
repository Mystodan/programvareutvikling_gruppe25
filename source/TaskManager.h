#pragma once
#include <memory>
#include <vector>

class Task;
//class User;

class TaskManager {
public:
	//static std::vector<std::shared_ptr<User>> get_all_users();
	static std::vector<std::shared_ptr<Task>> get_all_tasks();

	static void delete_task(Task task);
	static void add_task(Task task);
	static Task get_task(int task_id);
};
