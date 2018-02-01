#pragma once
#include <limits>

enum UserConfigurationResult
{
	Ok = 0,
    InvalidCategory = 1,
    InvalidTag = 2,
    InvalidValueType = 3,
    Other = INT_MAX
};