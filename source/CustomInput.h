#pragma once
#include <ftxui/component/input.hpp>

namespace ftxui {
	/**
	 * \brief Custom inputbox that doesn't capture left/right inputs.
	 * Also always keeps the cursor as far right as possible
	 */
	class CustomInput : public Input {
	public:
		bool OnEvent(ftxui::Event) override;

		Element Render() override;

		void set_content(const std::wstring& content);

		std::wstring original_content;

		std::function<bool()> on_enter_validate = []{ return false;};

		Decorator main_decorator = flex | size(HEIGHT, EQUAL, 1);
	};

}
