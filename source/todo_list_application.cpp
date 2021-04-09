/*
 * To-do-list application group 25
 * 
 *
 *
 *
 *  
 */

#include "SideMenu.h"
#include <vector>
#include <iostream>

#include "EmptyCheckBox.h"
#include "UsersTasks.h"
#include "Task.h"
#include "User.h"
#include "Category.h"

using namespace ftxui;

int main(int argc, const char* argv[]) {
    auto screen = ScreenInteractive::TerminalOutput();
    SideMenu sidemenu;
    screen.Loop(&sidemenu);
    return 0;
}