#include "EmptyCheckBox.h"

using namespace ftxui;
Element EmptyCheckBox::Render() {
	bool is_focused = Focused();
	auto style = is_focused ? focused_style : unfocused_style;
	auto focus_management = is_focused ? focus : state ? select : nothing;
	return hbox(text(state ? checked : unchecked) | style | focus_management | hcenter);
}
