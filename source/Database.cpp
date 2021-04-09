#include "database.h"

namespace Database {
	void insert_default_data() {
		using namespace Database;

		{ // Colors
			Color white{ 1, 0xFFFFFFFF };
			Database::add<Color>(white);

			Color red{ 2, 0xFF0000FF };
			Database::add<Color>(red);
		}
	}
}
