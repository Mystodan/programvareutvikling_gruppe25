/*
 *  To-do-list application group 25
 *
 *
 *
 *
 *
 */

#include "ftxui/component/container.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "ftxui/component/menu.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/toggle.hpp"
#include "ftxui/screen/string.hpp"
#include "ftxui/component/checkbox.hpp"
#include <vector>
#include <iostream>

using namespace ftxui;

class newTask {
public:
    bool isPriority,
        isComplete,
        inBin;
    int  status = 0,
        date,
        id;
    Menu temp;
};

class Tasks : public Component {
public:
    Tasks() {
        Add(&container_);
        container_.Add(&box_1_);
        container_.Add(&box_2_);
        container_.Add(&box_3_);
        box_1_.label = L"Build examples";
        box_2_.label = L"Build tests";
        box_3_.label = L"Use WebAssembly";
    }

    Element Render() override {
        auto menu_win = window(text(L"Tasks") | center, box_1_.Render()); // Makes window around menu
        return vbox({ menu_win });
    }
    std::function<void()> on_enter = []() {};

private:
    Menu task_;
    CheckBox box_1_;
    CheckBox box_2_;
    CheckBox box_3_;
    Container container_ = Container::Vertical();
};

class Priority : public Component {
public:
    Priority() {
        Add(&container_);
        container_.Add(&task_);

        task_.entries = {
            L"Task 4",
            L"Task 5",
            L"Task 6",
        };
    }
    Element Render() override {
        auto menu_win = window(text(L"Priority") | center, task_.Render()); // Makes window around menu
        return vbox({ menu_win });
    }

    std::function<void()> on_enter = []() {};

private:
    Menu task_;
    Container container_ = Container::Horizontal();
};

class Completed : public Component {
public:
    Completed() {
        Add(&container_);
        container_.Add(&task_);

        task_.entries = {
            L"Task 7",
            L"Task 8",
            L"Task 9",
            L"Task 10",
        };
    }
    Element Render() override {
        auto menu_win = window(text(L"Completed") | center, task_.Render()); // Makes window around menu
        return vbox({ menu_win });
    }

    std::function<void()> on_enter = []() {};

private:
    Menu task_;
    Container container_ = Container::Vertical();
};

class RecycleBin : public Component {
public:
    RecycleBin() {
        Add(&container_);
        container_.Add(&task_);

        task_.entries = {
            L"Task 7",
            L"Task 8",
            L"Task 9",
            L"Task 10",
        };
    }
    Element Render() override {
        auto menu_win = window(text(L"RecycleBin") | center, task_.Render()); // Makes window around menu
        return vbox({ menu_win });
    }

    std::function<void()> on_enter = []() {};

private:
    Menu task_;
    Container container_ = Container::Vertical();
};

class Tab : public Component {
public:
    Container main_container = Container::Horizontal();
    Container container = Container::Tab(&menu.selected);
    Menu menu;

    Tasks       td_Tasks;
    Priority    td_Priority;
    Completed   td_Completed;
    RecycleBin  td_RecycleBin;

    Tab() {
        Add(&main_container);
        main_container.Add(&menu);
        menu.entries = {
            L"Tasks",
            L"Priority",
            L"Completed",
            L"Recycle bin"
        };
        main_container.Add(&container);
        container.Add(&td_Tasks);
        container.Add(&td_Priority);
        container.Add(&td_Completed);
        container.Add(&td_RecycleBin);
    }

    Element Render() override {
        //auto menu_win = window(text(L"Side Menu") | center, menu.Render()); // Makes window around menu
        return vbox({
            text(L"To-do-list") | bold | hcenter,
                hbox({
                    hbox({ window(text(L"Side Menu") | center, menu.Render()) | center, container.Render()}),
                }) | border,
            });
    }
};

std::vector<newTask> gTask[];

int main(int argc, const char* argv[]) {
    auto screen = ScreenInteractive::TerminalOutput();
    Tab tab;
    screen.Loop(&tab);
    return 0;
}