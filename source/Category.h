#pragma once
#include <string>

struct Color;

struct Category {
	/*
	 * DB
	 */
	int id;
	std::string description;
	int priority;
	int color_id;

	/*
	 * Non DB
	 */
	Color get_color();
};
