#include "vtoggle.h"

#include <algorithm>

namespace ftxui {

    Element VToggle::Render() {
        bool is_focused = Focused();

        Elements children;
        for (size_t i = 0; i < entries.size(); ++i) {
            // Separator.
            if (i != 0)
                children.push_back(separator());

            // Entry.
            auto style = (selected != int(i))
                ? normal_style
                : is_focused ? focused_style : selected_style;
            auto focused = (selected != int(i)) ? nothing : is_focused ? focus : select;
            children.push_back(text(entries[i]) | style | focused);
        }
        return vbox(std::move(children));
    }

    bool VToggle::OnEvent(Event event) {
        int old_selected = selected;
        if (event == Event::ArrowUp || event == Event::Character('h'))
            selected--;
        if (event == Event::ArrowDown || event == Event::Character('l'))
            selected++;
        if (event == Event::Tab && entries.size())
            selected = (selected + 1) % entries.size();
        if (event == Event::TabReverse && entries.size())
            selected = static_cast<int>(selected + entries.size() - 1 % entries.size());

        selected = std::max(0, std::min(int(entries.size()) - 1, selected));

        if (old_selected != selected) {
            on_change();
            return true;
        }

        if (event == Event::Return) {
            on_enter();
            return true;
        }

        return false;
    }

}  // namespace ftxui

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.