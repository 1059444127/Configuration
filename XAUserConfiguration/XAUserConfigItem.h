#pragma once

#include <string>

struct XAUserConfigItem
{
	XAUserConfigItem():IsChanged(false)
	{
	}

	std::string Name;
	unsigned int Tag;
	std::string Value;
	bool IsChanged;
};
