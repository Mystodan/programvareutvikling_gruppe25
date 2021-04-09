#pragma once
#include <cassert>
#include <string>

struct Color;

struct CategoryDB {
	int id = -1;
	std::string description;
	int priority = -1;
	int color_id;

};

class Category {
public:
	Category(CategoryDB category_) : category_(category_) {
		assert(category_.id != -1);
	}

	int get_id() const;

	std::string get_description();
	void set_description(std::string description_);

	int get_priority();
	void set_priority(int priority);

	int get_color_id();
	void set_color_id(int color_id_);
	Color get_color();

private:
	void update();
	void fetch();

	// Could make this static and only hold the id of the object per instance
	CategoryDB category_{};
};
