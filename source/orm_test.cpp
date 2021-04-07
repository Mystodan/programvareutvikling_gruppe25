//#define SQLITE_MAIN
#ifdef SQLITE_MAIN
#include <iostream>
#include "database.h"

using namespace std;

//auto open_db(){
//	return sqlite_orm::make_storage("test.sqlite");
//}

int main() {
	//create_db();
	//User user{ -1, "Jonh", "Doe", 664416000, std::make_unique<std::string>("url_to_heaven"), 3 };

	//auto insertedId = storage.insert(user);
	//cout << "insertedId = " << insertedId << endl;      //  insertedId = 8
	//user.id = insertedId;

	//User secondUser{ -1, "Alice", "Inwonder", 831168000, {} , 2 };
	//insertedId = storage.insert(secondUser);
	//secondUser.id = insertedId;


	try {
		User user1{ 2, "firsty7y", "lastyy", 1 }; // Does not overwrite :)
		Database::add<User>(user1);
		auto user = Database::get<User>(2);
		cout << "user = " << user.id <<  " " << user.first_name << " " << user.last_name << endl;
	} catch (std::system_error& e) {
		cout << e.what() << endl;
	} catch (...) {
		cout << "unknown exeption" << endl;
	}

	return 0;
}

#endif
