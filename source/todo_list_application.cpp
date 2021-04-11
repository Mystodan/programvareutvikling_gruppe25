/*
 * To-do-list application group 25
 * 
 * This application allows you to add a new task, and then assign priority, description
 * status, category, start and enddate.
 *
 *  
 */
#include "SideMenu.h"

int main(int argc, const char* argv[]) {
    auto screen = ScreenInteractive::TerminalOutput();
    SideMenu sidemenu;
    screen.Loop(&sidemenu);
    return 0;
}