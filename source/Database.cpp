#include "database.h"

namespace Database {
	/**
	 * \brief Inserts new default data into the database
	 */
	[[unused]] void insert_default_data() {
		using namespace Database;

		{ // Colors
			Color white{ 1, 0xFFFFFFFF };
			Database::add<Color>(white);

			Color red{ 2, 0xFF0000FF };
			Database::add<Color>(red);
		}
	}
}
