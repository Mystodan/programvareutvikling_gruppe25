#include "CustomInput.h"
#include <Windows.h>

namespace ftxui {
	bool CustomInput::OnEvent(Event event) {
		cursor_position = std::max(0, std::min<int>(content.size(), cursor_position));
		//cursor_position = std::max(0, (int)content.size());
		std::wstring c;

		// Backspace.
		if (event == Event::Backspace) {
			if (cursor_position == 0)
				return false;
			content.erase(cursor_position - 1, 1);
			cursor_position--;
			on_change();
			return true;
		}

		// Delete
		if (event == Event::Delete) {
			if (cursor_position == int(content.size()))
				return false;
			content.erase(cursor_position, 1);
			on_change();
			return true;
		}

		// Enter.
		if (event == Event::Return) {
			// Override original content with what the user has selected
			if (on_enter_validate()) {
				original_content = content;
			}

			return true;
		}

		if (event == Event::Custom) {
			return false;
		}

		//if (event == Event::ArrowLeft && cursor_position > 0) {
		//	cursor_position--;
		//	OutputDebugStringA("Left");
		//	return false;
		//}

		//if (event == Event::ArrowRight && cursor_position < (int)content.size()) {
		//	cursor_position++;
		//	OutputDebugStringA("Right");
		//	return false;
		//}

		// Content
		if (event.is_character()) {
			content.insert(cursor_position, 1, event.character());
			cursor_position++;
			on_change();
			return true;
		}
		return false;
	}

	Element CustomInput::Render() {
		//cursor_position = std::max(0, std::min<int>(content.size(), cursor_position));

		// Always have it placed to the right of the text because we no longer have left/right control of the cursor
		cursor_position = std::max(0, (int)content.size());

		auto main_decorator = flex | size(HEIGHT, EQUAL, 1);
		bool is_focused = Focused();

		// Not focused.
		if (!is_focused)
			return text(original_content) | main_decorator;
			//return text(content) | main_decorator;

		// Placeholder.
		if (content.size() == 0) {
			if (is_focused)
				return text(placeholder) | focus | dim | inverted | main_decorator;
			else
				return text(placeholder) | dim | main_decorator;
		}


		std::wstring part_before_cursor = content.substr(0, cursor_position);
		std::wstring part_at_cursor = cursor_position < (int)content.size()
			                              ? content.substr(cursor_position, 1)
			                              : L" ";
		std::wstring part_after_cursor = cursor_position < (int)content.size() - 1
			                                 ? content.substr(cursor_position + 1)
			                                 : L"";
		auto focused = is_focused ? focus : select;

		return
			hbox(
				text(part_before_cursor),
				text(part_at_cursor) | underlined | focused,
				text(part_after_cursor)
			) | flex | inverted | frame | main_decorator;
	}

	void CustomInput::set_content(const std::wstring& content_) {
		content = content_;
		original_content = content_;
	}
}
