#pragma once
#include "XAConfiguration/IUserConfiguration.h"
#include "XAUserConfigurationExportMacro.h"
#include <McsfFileParser/mcsf_ifile_parser.h>

class XA_UserConfiguration_Export XAUserConfiguration : public IUserConfiguration
{
public:
	void Init();
	XAUserConfiguration();
	virtual int LoadUserConfig(unsigned category);
	virtual int SaveUserConfig(unsigned category);
	virtual int SetUserConfig(unsigned category, unsigned tag, const std::string& value);
	virtual int GetUserConfig(unsigned category, unsigned tag, std::string& value);
	virtual ~XAUserConfiguration();
private:
	Mcsf::IFileParser* _pFileParser;
};
