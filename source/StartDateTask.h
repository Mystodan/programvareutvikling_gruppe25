#pragma once

#include <Windows.h>
/*
 *
 */

#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"
#include <ctime>
#include <string>

using namespace ftxui;

class StartDateTask : public Component {
public:
    StartDateTask() {
        Add(&container_);
        container_.Add(&status_);
    }
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
    std::function<void()> on_enter = []() {};

private:
    Menu status_;
    Container container_ = Container::Vertical();
};
