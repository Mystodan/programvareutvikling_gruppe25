#pragma once

#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"
#include <ctime>
#include <string>

class Task;

class StartDateTask : public ftxui::Component {
public:
    StartDateTask() {
        Add(&container_);
        container_.Add(&status_);
    }
<<<<<<< HEAD
    void fill_data(const std::vector<std::shared_ptr<Task>>& tasks) {
        status_.entries.clear();
        for (const auto& task : tasks) {
            wchar_t buffer[9];
            time_t unixTime = task->get_start_time();
            struct tm tm_;
            localtime_s(&tm_,&unixTime);
            wcsftime(buffer, sizeof(buffer), L"%d.%m.%y", &tm_);
            status_.entries.push_back(buffer);
        }
    }
=======

    void fill_data(const std::vector<std::shared_ptr<Task>>& tasks);
    void add_task(const std::shared_ptr<Task>& task);
    void clear();

>>>>>>> 95c8a79fae04051727a99faf5776dacc80e5f7f6
    std::function<void()> on_enter = []() {};

private:
    ftxui::Menu status_;
    ftxui::Container container_ = ftxui::Container::Vertical();
};
