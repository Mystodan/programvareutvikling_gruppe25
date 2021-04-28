#include "HelpWindow.h"

namespace ftxui {
	// TODO: Implement help window content
	Element HelpWindow::Render() {
		Element ele = window(text(L"Help menu"), text(L""));
		return ele;
	}
}
