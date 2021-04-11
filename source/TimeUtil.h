#pragma once

#include <memory>
#include "Task.h"

namespace Utils {
	
	std::wstring unixtime_to_string(int unix_time);

	int string_to_unixtime(std::wstring str_time);

}