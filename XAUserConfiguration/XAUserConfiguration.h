#pragma once
#include "XAConfiguration/IUserConfiguration.h"
#include "XAUserConfigurationExportMacro.h"
#include <McsfFileParser/mcsf_ifile_parser.h>
#include <map>
#include "XAUserConfigItem.h"

class XA_UserConfiguration_Export XAUserConfiguration : public IUserConfiguration
{
public:
	XAUserConfiguration();
	virtual int LoadUserConfig(unsigned category);
	virtual int SaveUserConfig(unsigned category);
	virtual int SetUserConfig(unsigned category, unsigned tag, int& value);
	virtual int GetUserConfig(unsigned category, unsigned tag, int value);
	virtual int SetUserConfig(unsigned category, unsigned tag, double& value);
	virtual int GetUserConfig(unsigned category, unsigned tag, double value);
	virtual int SetUserConfig(unsigned category, unsigned tag, bool& value);
	virtual int GetUserConfig(unsigned category, unsigned tag, bool value);
	virtual int SetUserConfig(unsigned category, unsigned tag, const std::string& value);
	virtual int GetUserConfig(unsigned category, unsigned tag, std::string& value);
	virtual ~XAUserConfiguration();
private:
	Mcsf::IFileParser* _pFileParser;
	std::map<unsigned int, std::string> _categoryLocationMap;
	std::map<unsigned int, std::map<unsigned int, XAUserConfigItem>> _configItems;
	std::string GetUserSettingDir(unsigned int category);
	void Init();
};
