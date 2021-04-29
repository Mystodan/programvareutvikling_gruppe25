#pragma once
#include "Task.h"

namespace Utils {
	
	std::wstring unixtime_to_string(int unix_time); // Converts from unixTime to string

	int string_to_unixtime(std::wstring str_time); // Converts from string to unixTime

}