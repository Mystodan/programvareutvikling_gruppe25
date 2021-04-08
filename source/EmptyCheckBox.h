#pragma once
#include <ftxui/component/checkbox.hpp>

class EmptyCheckBox : public ftxui::CheckBox {
public:
	ftxui::Element Render() override;
	  std::wstring checked = L"[X]";    /// Prefix for  a "checked" state.
	  std::wstring unchecked = L"[ ]";  /// Prefix for  an "unchecked" state.
};

