//#include "Category.h"
//
//#include "Database.h"
//
//int Category::get_color_id() {
//	fetch();
//
//	return category_.color_id;
//}
//
//void Category::set_color_id(int color_id_) {
//	category_.color_id = color_id_;
//
//	update();
//}
//
//Color Category::get_color() {
//	fetch();
//
//	return Database::get<Color>(category_.color_id);
//}
//
//int Category::get_id() const {
//	return category_.id;
//}
//
//std::wstring Category::get_description() {
//	fetch();
//	return category_.description;
//}
//
//void Category::set_description(std::wstring description_) {
//	category_.description = description_;
//
//	update();
//}
//
//int Category::get_priority() {
//	fetch();
//
//	return category_.priority;
//}
//
//void Category::set_priority(int priority_) {
//	category_.priority = priority_;
//
//	update();
//}
//
//void Category::update() {
//	Database::update<CategoryDB>(category_);
//}
//
//void Category::fetch() {
//	category_ = Database::get<CategoryDB>(category_.id);
//}
