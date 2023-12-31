#include "HelpWindow.h"

namespace ftxui {
	/**
	 * \brief Renders HelpWindow component
	 * \return Element to be rendered
	 */
	Element HelpWindow::Render() {
		return window(text(L"Help menu"),
		vbox({
				text(L"Use the enter/space key to click on options."),
				// left up down right
				// https://en.wikipedia.org/wiki/Arrow_(symbol)
				hbox({text(L"Navigate with the arrow keys "), text(L"\x2190 \x2191 \x2193 \x2192") | bold}),
				text(L"Sort the tasks with the 'F' keys (for example: F1)")
			}));
	}
}
