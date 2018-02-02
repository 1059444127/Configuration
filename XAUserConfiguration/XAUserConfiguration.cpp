#include "XAUserConfiguration.h"
#include <McsfFileParser/mcsf_file_parser_factory.h>
#include "XAConfiguration/XAConfigurationLogger.h"
#include "Common/McsfSystemEnvironmentConfig/mcsf_systemenvironment_factory.h"
#include <XAConfiguration/XAConfigurationMacro.h>

void XAUserConfiguration::Init()
{
	_pFileParser = Mcsf::ConfigParserFactory::Instance()->GetXmlFileParser();
	_pFileParser->Initialize();

	Mcsf::ISystemEnvironmentConfig* pSysConfig =
		Mcsf::ConfigSystemEnvironmentFactory::Instance()->GetSystemEnvironment();
	std::string userConfigPath = pSysConfig->GetApplicationPath(USER_CONFIG_PATH);
	std::string categoryIndexFilePath = userConfigPath + CONFIG_INDEX_FILE;

	if(!_pFileParser->ParseByURI(categoryIndexFilePath))
	{
		LOG_ERROR_XA_Configuration << "Failed to parse Config " << categoryIndexFilePath << LOG_END;
		return;
	}

	std::vector<std::string> configNodes;
	if(!_pFileParser->GetStringValueByTag(CONFIG_ITEM, &configNodes))
	{
		LOG_ERROR_XA_Configuration << "Failed to parse Tag " << CONFIG_ITEM << LOG_END;
		return;
	}
	
	for (auto iter = configNodes.begin(); iter!= configNodes.end(); iter++)
	{
		std::string name;
		if(!_pFileParser->GetAttributeStringValue(*iter, NAME_ATTRIBUTE, &name))
		{
			LOG_ERROR_XA_Configuration << "Failed to Get Attribute [" << NAME_ATTRIBUTE  << "] From " << *iter << LOG_END;
			continue;
		}
		std::string location;
		if(!_pFileParser->GetAttributeStringValue(*iter, LOCATION_ATTRIBUTE, &location))
		{
			LOG_ERROR_XA_Configuration << "Failed to Get Attribute [" << LOCATION_ATTRIBUTE << "] From " << *iter << LOG_END;
			continue;
		}
		_configItems[name] = location;
	}

}

XAUserConfiguration::XAUserConfiguration() : _configItems()
{
	Init();
}

int XAUserConfiguration::LoadUserConfig(unsigned category)
{
	LOG_INFO_XA_Configuration << "Load User Config with category [" << category << "]" << LOG_END;
	return 0;
}

int XAUserConfiguration::SaveUserConfig(unsigned category)
{
	LOG_INFO_XA_Configuration << "Save User Config with category [" << category << "]" << LOG_END;
	return 0;
}

int XAUserConfiguration::SetUserConfig(unsigned category, unsigned tag, const std::string& value)
{
	LOG_INFO_XA_Configuration << "Set User Config with category [" << category << "] for tag [" << tag << "] of value [" << value << "]" << LOG_END;
	return 0;
}

int XAUserConfiguration::GetUserConfig(unsigned category, unsigned tag, std::string& value)
{
	LOG_INFO_XA_Configuration << "Get User Config with category [" << category << "] for tag [" << tag << "] of value [" << value << "]" << LOG_END;
	return 0;
}

XAUserConfiguration::~XAUserConfiguration()
{
	if(nullptr != _pFileParser)
	{
		_pFileParser->Terminate();
		delete _pFileParser;
		_pFileParser = nullptr;
	}
}


//TODO: Add EA Chart to source control
//TODO: Add Sample Containee
