#include "TimeUtil.h"
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

/**
* \Function to imitate unix version of strptime on windows-versions
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
	* \Converts unixTime (int) to date (dd.mm.yy) (wstring)
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
	* \Converts date (dd.mm.yy) (wstring) to unixTime (int)
	* \param wstring to be converted to unixTime
	* \return unixTime
	*/
	int string_to_unixtime(std::wstring str_time) {
		struct tm tm; // Struct storing time structure
		time_t unixTime = 0; // Will be used to store converted unixTime
		memset(&tm, 0, sizeof(tm)); // Empties tm struct

		std::wstring wdate(str_time);
		std::string sdate(wdate.begin(), wdate.end()); // Converts wstring to string
		int length = sdate.size();
		char* cdate;
		cdate = &sdate[0]; // Converts string to char date

		strptime(cdate, "%d.%m.%y", &tm); // Converts char date to tm structure

		// TODO: Further input validation
		// For now 10.04.2a works, should not work
		// For now 10.04.20a works, should not work
		
		unixTime = mktime(&tm); // Converts tm structure to unixTime

		return unixTime;
	}
}
