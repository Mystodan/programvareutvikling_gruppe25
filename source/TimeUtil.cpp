#include "TimeUtil.h"
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>


extern "C" char* strptime(const char* s, const char* f, struct tm* tm) {
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
	* \param unixTime to be converted to wstring
	* \return wstring
	*/
	std::wstring unixtime_to_string(int unix_time) {
		wchar_t buffer[9];
		time_t unixTime = unix_time;
		struct tm tm_;
		localtime_s(&tm_, &unixTime);
		wcsftime(buffer, sizeof(buffer), L"%d.%m.%y", &tm_);

		return std::wstring(buffer);
	}

	/**
	* \Converts date (dd.mm.yy) (wstring) to unixTime (int)
	* \param wstring to be converted to unixTime
	* \return unixTime
	*/
	int string_to_unixtime(std::wstring str_time) {
		
		struct tm tm;
		time_t unixTime = 0;
		memset(&tm, 0, sizeof(tm));

		std::wstring wdate(str_time);
		std::string sdate(wdate.begin(), wdate.end());
		int length = sdate.size();
		char* cdate;
		cdate = &sdate[0];

		strptime(cdate, "%d.%m.%y", &tm);

		unixTime = mktime(&tm);

		return unixTime;
	}
}
