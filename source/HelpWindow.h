#pragma once
#include <ftxui/component/component.hpp>

namespace ftxui {
	/**
	 * \brief Help window tab
	 */
	class HelpWindow : public Component {
	public:
		Element Render() override;

		std::wstring original_content;

		std::function<bool()> on_enter_validate = []{ return false;};
	};

}
