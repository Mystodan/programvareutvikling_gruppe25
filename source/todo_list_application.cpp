/*
 * To-do-list application group 25
 * 
 * 
 * 
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