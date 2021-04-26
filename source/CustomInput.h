#pragma once
#include <ftxui/component/input.hpp>

namespace ftxui {
	class CustomInput : public Input {
	public:
		bool OnEvent(ftxui::Event) override;

		Element Render() override;

		void set_content(const std::wstring& content);

		std::wstring original_content;

		std::function<bool()> on_enter_validate = []{ return false;};
	};

}
