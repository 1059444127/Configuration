#pragma once

class IUserConfiguration
{
public:
	virtual int LoadUserConfig(unsigned int category) = 0;
	virtual int SaveUserConfig(unsigned int category) = 0;
	virtual int SetUserConfig(unsigned int category, unsigned int tag, const std::string& value) = 0;
	virtual int GetUserConfig(unsigned int category, unsigned int tag, std::string& value) = 0;

	virtual ~IUserConfiguration() {};
};