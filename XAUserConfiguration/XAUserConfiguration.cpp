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
		_categoryLocationMap[uiCategory] = location;
	}

}

XAUserConfiguration::XAUserConfiguration() : _categoryLocationMap(), _configItems()
{
	Init();
}

int XAUserConfiguration::LoadUserConfig(unsigned category)
{
	LOG_INFO_XA_Configuration << "Load User Config with category [" << category << "]" << LOG_END;
	auto iter = _categoryLocationMap.find(category);
	if(iter == _categoryLocationMap.end()) {return UserConfigurationResult::InvalidCategory;}

	std::string sUserSettingDir = iter->second;
	//std::string sUserSettingDir = "D:\\X-SW\\XA\\Trunk\\UIH\\appdata\\user_settings\\users\\default_user\\config\\exam\\ExamConfig.xml";//iter->second;
	//std::string sUserSettingDir = "D:\\X-SW\\XA\\Trunk\\UIH\\appdata\\user_settings\\users\\default_user\\config\\exam\\ExamConfig.xml";//iter->second;

	if(!_pFileParser->OpenFromUserSettingsDir(sUserSettingDir))
	{
		LOG_ERROR_XA_Configuration << "Fail to Get File Content From User Setting Dir [" << sUserSettingDir << "]" << LOG_END;
		return UserConfigurationResult::InvalidFile;
	}

	int itemNumber;
	if(!_pFileParser->GetElementNumber(CONFIG_ITEM, &itemNumber))
	{
		LOG_ERROR_XA_Configuration << "Failed to parse Tag " << CONFIG_ITEM << LOG_END;
		return UserConfigurationResult::InvalidFile;		
	}



	std::map<unsigned int, XAUserConfigItem> userConfigItemMap;
	for (int i=0; i<itemNumber; i++)
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
		std::string name;
		if(!_pFileParser->GetAttributeStringValue(itemConfigPath, NAME_ATTRIBUTE, &name))
		{
			LOG_ERROR_XA_Configuration << "Failed to Get Attribute [" << NAME_ATTRIBUTE << "] From " << itemConfigPath << LOG_END;
			continue;
		}

		std::string value;
		if(!_pFileParser->GetAttributeStringValue(itemConfigPath, VALUE_ATTRIBUTE, &value))
		{
			LOG_ERROR_XA_Configuration << "Failed to Get Attribute [" << VALUE_ATTRIBUTE << "] From " << itemConfigPath << LOG_END;
			continue;
		}

		istringstream is(id);
		unsigned int tag;
		is >> tag;

		XAUserConfigItem item;
		item.Name = name;
		item.Tag = tag;
		item.Value = value;
		userConfigItemMap[tag] = item; 
	}

	_configItems[category] = userConfigItemMap;

	return 0;
}

int XAUserConfiguration::SaveUserConfig(unsigned category)
{
	LOG_INFO_XA_Configuration << "Save User Config with category [" << category << "]" << LOG_END;
	//TODO: 发送更新通知
	return 0;
}


std::string XAUserConfiguration::GetUserSettingDir(unsigned category)
{
	LOG_INFO_XA_Configuration << "Get User Setting Dir of category [" << category << "]" << LOG_END;
	auto iter =_categoryLocationMap.find(category);
	if(iter == _categoryLocationMap.end()) return XA_CONFIGURATION_EMPTY_STRING;
	return iter->second;
}

int XAUserConfiguration::SetUserConfig(unsigned category, unsigned tag, const std::string& value)
{
	LOG_INFO_XA_Configuration << "Set User Config with category [" << category << "] for tag [" << tag << "] of value [" << value << "]" << LOG_END;
	std::string userSettingDir = GetUserSettingDir(category);
	if(userSettingDir.length() <= 0) {return UserConfigurationResult::InvalidCategory;}

	

	return 0;
}

int XAUserConfiguration::GetUserConfig(unsigned category, unsigned tag, std::string& value)
{
	LOG_INFO_XA_Configuration << "Get User Config with category [" << category << "] for tag [" << tag << "]" << LOG_END;

	auto categoryIter = _configItems.find(category);
	if(categoryIter == _configItems.end())
	{
		LOG_ERROR_XA_Configuration << "No category [" << category << "] in Config Cache" << LOG_END;
		return UserConfigurationResult::InvalidCategory;
	}

	auto tagIter = categoryIter->second.find(tag);
	if(tagIter == categoryIter->second.end())
	{
		LOG_ERROR_XA_Configuration << "No Tag [" << tag << "] in Config Cache" << LOG_END;
		return UserConfigurationResult::InvalidTag;
	}

	value = tagIter->second.Value;

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
//FileParser: http://alpha:8099/redmine/boards/12/topics/163
