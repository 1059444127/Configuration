#pragma once
#include "XAConfiguration/IUserConfiguration.h"
#include "XAUserConfigurationExportMacro.h"
#include <McsfFileParser/mcsf_ifile_parser.h>
#include <map>
#include "XAUserConfigItem.h"
#include "XAConfiguration/XAConfigurationMacro.h"
#include "XAConfiguration/IConfigurationSubject.h"
#include "McsfNetBase\mcsf_communication_proxy.h"

class XA_UserConfiguration_Export XAUserConfiguration : public IUserConfiguration
{
public:
	XAUserConfiguration();
	virtual int LoadUserConfig(unsigned category);
	virtual int SaveUserConfig(unsigned category);
	virtual int SetUserConfig(unsigned category, unsigned tag, const std::string& value);
	virtual int GetUserConfig(unsigned category, unsigned tag, std::string& value);
	virtual void SetCommunicationProxy(Mcsf::ICommunicationProxy* proxy) {_proxy = proxy;}
	virtual ~XAUserConfiguration();
private:
	Mcsf::IFileParser* _pFileParser;
	std::map<unsigned int, std::string> _categoryLocationMap;
	std::map<unsigned int, std::map<unsigned int, XAUserConfigItem>> _configItems;
	std::string GetUserSettingDir(unsigned int category);
	std::string GetElementPath(unsigned int category,unsigned int tag);	
	Mcsf::ICommunicationProxy* _proxy;
	void Init();
	void NotifyUserSettingChanged(unsigned int category);

	XA_Configuration_DISALLOW_COPY_AND_ASSIGN(XAUserConfiguration);
};
