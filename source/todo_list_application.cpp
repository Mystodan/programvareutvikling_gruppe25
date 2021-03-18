#include <iostream>
#include <cmath>
#include <thread>

#include "ftxui/component/checkbox.hpp"
#include "ftxui/component/container.hpp"
#include "ftxui/component/input.hpp"
#include "ftxui/component/menu.hpp"
#include "ftxui/component/radiobox.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/toggle.hpp"
#include "ftxui/screen/string.hpp"

using namespace ftxui;

int shift = 0;
class Graph {
public:
	std::vector<int> operator()(int width, int height) {
		std::vector<int> output(width);
		for (int i = 0; i < width; ++i) {
			float v = 0;
			v += 0.1f * sin((i + shift) * 0.1f);
			v += 0.2f * sin((i + shift + 10) * 0.15f);
			v += 0.1f * sin((i + shift) * 0.03f);
			v *= height;
			v += 0.5f * height;
			output[i] = (int)v;
		}
		return output;
	}
};

/**
 * \brief HTop component/tab
 */
class HTopComponent : public Component {
	Graph my_graph;

public:
	HTopComponent() {}
	~HTopComponent() override {}

	Element Render() override {
		auto frequency = vbox({
			text(L"Frequency [Mhz]") | hcenter,
			hbox({
				vbox({
					text(L"2400 "),
					filler(),
					text(L"1200 "),
					filler(),
					text(L"0% "),
				}),
				graph(std::ref(my_graph)) | flex,
			}) | flex,
			});

		auto utilization = vbox({
			text(L"Utilization [%]") | hcenter,
			hbox({
				vbox({
					text(L"100 "),
					filler(),
					text(L"50 "),
					filler(),
					text(L"0 "),
				}),
				graph(std::ref(my_graph)) | color(Color::RedLight),
			}) | flex,
			});

		auto ram = vbox({
			text(L"Ram [Mo]") | hcenter,
			hbox({
				vbox({
					text(L"8192"),
					filler(),
					text(L"4096 "),
					filler(),
					text(L"0 "),
				}),
				graph(std::ref(my_graph)) | color(Color::BlueLight),
			}) | flex,
			});

		return hbox({
				   vbox({
					   frequency | flex,
					   separator(),
					   utilization | flex,
				   }) | flex,
				   separator(),
				   ram | flex,
			}) |
			flex | border;
	}
};

/**
 * \brief Spinner component/tab
 */
class SpinnerComponent : public Component {
  Element Render() override {
    Elements entries;
    for (int i = 0; i < 22; ++i) {
      if (i != 0)
        entries.push_back(spinner(i, shift / 2) | bold |
                          size(WIDTH, GREATER_THAN, 2) | border);
    }
    return hflow(std::move(entries)) | border;
  }
};

/**
 * \brief Tab manager, keeps track of custom tab components
 */
class Tab : public Component {
public:
	Container main_container = Container::Vertical();

	Toggle tab_selection;
	Container container = Container::Tab(&tab_selection.selected);

	HTopComponent htop_component;
	SpinnerComponent spinner_component;

	Tab() {
		Add(&main_container);
		main_container.Add(&tab_selection);
		tab_selection.entries = {
			L"htop", L"spinner",
		};
		main_container.Add(&container);
		container.Add(&htop_component);
		container.Add(&spinner_component);
	}

	Element Render() override {
		return vbox({
			text(L"TODO List Application") | bold | hcenter,	// Bold text and horizontal centering
			tab_selection.Render() | hcenter,					// Horizontal centering
			container.Render() | flex,							// Flex/adaptive to terminal size
			});
	}
};
int main() {
	auto screen = ScreenInteractive::Fullscreen();

	std::thread update([&screen]() {
		while (true) {
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(0.05s);
			shift++;							// Shift the graphs
			screen.PostEvent(Event::Custom);	// Post an even to cause the application to redraw the screen
		}
		});

	Tab tab;
	screen.Loop(&tab);

	return EXIT_SUCCESS;
}
