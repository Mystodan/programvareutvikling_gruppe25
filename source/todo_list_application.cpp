/*
 * To-do-list application group 25
 * 
 * This application allows you to add a new task, and then assign priority, description
 * status, category, start and end date.
 *
 *  
 */
#include "SideMenu.h"

/**
 * \brief Main entry
 * \return exit status
 */
int main() {
    // Set up an interactive terminal
    auto screen = ScreenInteractive::TerminalOutput();

    // Create the main menu
    SideMenu sidemenu;

    // Loop until program exit and catch all events and inputs
    screen.Loop(&sidemenu);

    return 0;
}