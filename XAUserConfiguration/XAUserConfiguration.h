#pragma once
#include "XAConfiguration/IUserConfiguration.h"

class XAUserConfiguration : public IUserConfiguration
{
public:
	virtual int LoadUserConfig(unsigned category);
	virtual int SaveUserConfig(unsigned category);
	virtual int SetUserConfig(unsigned category, unsigned tag, const std::string& value);
	virtual int GetUserConfig(unsigned category, unsigned tag, std::string& value);
	virtual ~XAUserConfiguration();
};
