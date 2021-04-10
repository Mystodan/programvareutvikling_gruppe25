#include "TimeUtil.h"

namespace Utils {
	
	std::wstring unixtime_to_string(int unix_time) {
		wchar_t buffer[9];
		time_t unixTime = unix_time;
		struct tm tm_;
		localtime_s(&tm_, &unixTime);
		wcsftime(buffer, sizeof(buffer), L"%d.%m.%y", &tm_);

		return std::wstring(buffer);
	}

	int string_to_unixtime(std::wstring str_time) {
		return 0;
	}
}