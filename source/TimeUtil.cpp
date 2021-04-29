#include "TimeUtil.h"
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

// wchar_t to char is fine in our case
#pragma warning( disable : 4244 ) 

/**
* \brief Function to imitate unix version of strptime on windows-versions
* \param s input char which will be converted to unixTime
* \param f specifies which format parameter s is in
* \param tm where output of strptime will be stored
* \returns char arr with dd.mm.yy format
* 
* Code used from https://stackoverflow.com/a/33542189
*/
char* strptime(const char* s, const char* f, struct tm* tm) {
	std::istringstream input(s);
	input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
	input >> std::get_time(tm, f);
	if (input.fail()) {
		return nullptr;
	}
	return (char*)(s + input.tellg());
}

namespace Utils {
	
	/**
	* \brief Converts unixTime (int) to date (dd.mm.yy) (wstring)
	* \param unix_time to be converted to wstring
	* \return wstring
	*/
	std::wstring unixtime_to_string(int unix_time) {
		wchar_t buffer[9];
		time_t unixTime = unix_time; // Sets unix_time to time_t
		struct tm tm_; // Struct storing time structure
		localtime_s(&tm_, &unixTime); // Converts unixTime to readable/calendar time (local)
		wcsftime(buffer, sizeof(buffer), L"%d.%m.%y", &tm_); // Converts time to wchar, gets stored in buffer

		return std::wstring(buffer);
	}

	/**
	* \brief Converts date (dd.mm.yy) (wstring) to unixTime (int)
	* \param str_time to be converted to unixTime
	* \return unixTime
	*/
	int string_to_unixtime(std::wstring str_time) {
		tm tm{};								// Struct storing time structure
		memset(&tm, 0, sizeof(tm));		// Empties tm struct

		const std::string sdate(str_time.begin(), str_time.end()); // Converts wstring to string

		// Further input validation
		int day, month, year;
		if (swscanf_s(str_time.c_str(), L"%2d.%2d.%2d", &day, &month, &year) != 3) {
			return -1;
		}

		strptime(sdate.c_str(), "%d.%m.%y", &tm); // Converts char date to tm structure


		auto unixTime = mktime(&tm); // Converts tm structure to unixTime

		return static_cast<int>(unixTime);
	}
}
