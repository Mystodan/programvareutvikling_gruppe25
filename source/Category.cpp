#include "Category.h"

#include "Database.h"
#include "Color.h"

Color Category::get_color() {
	return Database::get<Color>(color_id);
}
