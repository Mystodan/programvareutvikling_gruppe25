/*
 * To-do-list application group 25
 * 
 *
 *
 *
 *  
 */
#include <iomanip>

#include "SideMenu.h"
#include "ftxui/component/menu.hpp"
#include "SideMenu.h"
#include "Task.h"

char* strptime(const char* s,
	const char* f,
	struct tm* tm) {
	std::istringstream input(s);
	input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
	input >> std::get_time(tm, f);
	if (input.fail()) {
		return nullptr;
	}
	return (char*)(s + input.tellg());
}

int main(int argc, const char* argv[]) {
	
    return 1;
    auto screen = ScreenInteractive::TerminalOutput();
    SideMenu sidemenu;
    screen.Loop(&sidemenu);
    return 0;
}