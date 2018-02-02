#include "XAUserConfiguration.h"
#include <McsfFileParser/mcsf_file_parser_factory.h>
#include "XAConfiguration/XAConfigurationLogger.h"
#include "Common/McsfSystemEnvironmentConfig/mcsf_systemenvironment_factory.h"
#include <XAConfiguration/XAConfigurationMacro.h>
#include "XAConfiguration/UserConfigurationResult.h"

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

	int configItemCount;
	if(!_pFileParser->GetElementNumber(CONFIG_ITEM, &configItemCount))
	{
		LOG_ERROR_XA_Configuration << "Failed to parse Tag " << CONFIG_ITEM << LOG_END;
		return;
	}

	
	for (int i=0; i<configItemCount; i++)
	{
		std::ostringstream os;
		os << CONFIG_ITEM << "[" << i << "]";
		std::string itemConfigPath = os.str();

		std::string id;
		if(!_pFileParser->GetAttributeStringValue(itemConfigPath, ID_ATTRIBUTE, &id))
		{
			LOG_ERROR_XA_Configuration << "Failed to Get Attribute [" << ID_ATTRIBUTE  << "] From " << itemConfigPath << LOG_END;
			continue;
		}
		std::string location;
		if(!_pFileParser->GetAttributeStringValue(itemConfigPath, LOCATION_ATTRIBUTE, &location))
		{
			LOG_ERROR_XA_Configuration << "Failed to Get Attribute [" << LOCATION_ATTRIBUTE << "] From " << itemConfigPath << LOG_END;
			continue;
		}

		istringstream is(id);
		unsigned int uiCategory;
		is >> uiCategory;
		_configItems[uiCategory] = location;
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

int XAUserConfiguration::SetUserConfig(unsigned category, unsigned tag, int& value)
{
	return 0;
}

int XAUserConfiguration::GetUserConfig(unsigned category, unsigned tag, int value)
{
	return 0;
}

int XAUserConfiguration::SetUserConfig(unsigned category, unsigned tag, double& value)
{
	return 0;
}

int XAUserConfiguration::GetUserConfig(unsigned category, unsigned tag, double value)
{
	return 0;
}

int XAUserConfiguration::SetUserConfig(unsigned category, unsigned tag, bool& value)
{
	return 0;
}

int XAUserConfiguration::GetUserConfig(unsigned category, unsigned tag, bool value)
{
	return 0;
}

std::string XAUserConfiguration::GetUserSettingDir(unsigned category)
{
	LOG_INFO_XA_Configuration << "Get User Setting Dir of category [" << category << "]" << LOG_END;
	auto iter =_configItems.find(category);
	if(iter == _configItems.end()) return XA_CONFIGURATION_EMPTY_STRING;
	return iter->second;
}

int XAUserConfiguration::SetUserConfig(unsigned category, unsigned tag, const std::string& value)
{
	LOG_INFO_XA_Configuration << "Set User Config with category [" << category << "] for tag [" << tag << "] of value [" << value << "]" << LOG_END;
	return 0;
}

int XAUserConfiguration::GetUserConfig(unsigned category, unsigned tag, std::string& value)
{
	LOG_INFO_XA_Configuration << "Get User Config with category [" << category << "] for tag [" << tag << "] of value [" << value << "]" << LOG_END;
	std::string userSettingDir = GetUserSettingDir(category);
	if(userSettingDir.length() <= 0) {return UserConfigurationResult::InvalidCategory;}

	return UserConfigurationResult::Ok;
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
//TODO: Received User Configuration Changed Event
