/*
 * To-do-list application group 25
 * 
 *
 *
 *
 *  
 */
#include "SideMenu.h"
#include "ftxui/component/menu.hpp"
#include "SideMenu.h"
#include "Task.h"

 // TODO: figure this out and have one vector of these base components in the tab class and then call fill_data from those base components to fill from vec
class BaseTask : public Component {
public:
    void fill_data(const std::vector<Task>& tasks);
};

int main(int argc, const char* argv[]) {
    auto screen = ScreenInteractive::TerminalOutput();
    SideMenu sidemenu;
    screen.Loop(&sidemenu);
    return 0;
}