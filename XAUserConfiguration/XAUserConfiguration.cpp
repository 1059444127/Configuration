#include "XAUserConfiguration.h"
#include <McsfFileParser/mcsf_file_parser_factory.h>
#include "XAConfiguration/XAConfigurationLogger.h"
#include "Common/McsfSystemEnvironmentConfig/mcsf_systemenvironment_factory.h"
#include <XAConfiguration/XAConfigurationMacro.h>
#include "XAConfiguration/UserConfigurationResult.h"
#include "CommunicationEventID.h"
#include <boost/lexical_cast.hpp>  

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

XAUserConfiguration::XAUserConfiguration() 
	: _categoryLocationMap()
	, _configItems()
	, _proxy(nullptr)
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

	for(int i=0; i<itemNumber; i++)
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

		istringstream is(id);
		unsigned int categoryid;
		is >> categoryid;
		// TODO: Using boost library

		if(category==categoryid)
		{
			int itemChildNumber;
			std::ostringstream child_index_os;
			child_index_os <<itemConfigPath <<CONFIG_ITEM;
			std::string itemChildIndexConfigPath = child_index_os.str();
			if(!_pFileParser->GetElementNumber(itemChildIndexConfigPath, &itemChildNumber))
			{
				LOG_ERROR_XA_Configuration << "Failed to parse Tag " << itemChildIndexConfigPath << LOG_END;
				return UserConfigurationResult::InvalidFile;		
			}

			std::map<unsigned int, XAUserConfigItem> userConfigItemMap;
			for (int j=0; j<itemChildNumber; j++)
			{
				std::ostringstream childos;
				childos <<itemConfigPath <<CONFIG_ITEM<< "[" << j << "]";
				std::string itemChildConfigPath = childos.str();

				std::string cid;
				if(!_pFileParser->GetAttributeStringValue(itemChildConfigPath, ID_ATTRIBUTE, &cid))
				{
					LOG_ERROR_XA_Configuration << "Failed to Get Attribute [" << ID_ATTRIBUTE  << "] From " << itemChildConfigPath << LOG_END;
					continue;
				}
				std::string name;
				if(!_pFileParser->GetAttributeStringValue(itemChildConfigPath, NAME_ATTRIBUTE, &name))
				{
					LOG_ERROR_XA_Configuration << "Failed to Get Attribute [" << NAME_ATTRIBUTE << "] From " << itemChildConfigPath << LOG_END;
					continue;
				}

				std::string value;
				if(!_pFileParser->GetAttributeStringValue(itemChildConfigPath, VALUE_ATTRIBUTE, &value))
				{
					LOG_ERROR_XA_Configuration << "Failed to Get Attribute [" << VALUE_ATTRIBUTE << "] From " << itemChildConfigPath << LOG_END;
					continue;
				}

				istringstream is(cid);
				unsigned int tag;
				is >> tag;

				XAUserConfigItem item;
				item.Name = name;
				item.Tag = tag;
				item.Value = value;
				userConfigItemMap[tag] = item; 
			}

			_configItems[category] = userConfigItemMap;
		}
	}

	return 0;
}

int XAUserConfiguration::SaveUserConfig(unsigned category)
{
	LOG_INFO_XA_Configuration << "Save User Config with category [" << category << "]" << LOG_END;

	auto iter= _configItems.find(category);
	if(iter == _configItems.end()) 
	{
		LOG_INFO_XA_Configuration << "Invalid Category [" << category << "]" << LOG_END;
		return UserConfigurationResult::InvalidCategory;
	}


	// Open file
	auto iter_dir = _categoryLocationMap.find(category);
	if(iter_dir == _categoryLocationMap.end()) {return UserConfigurationResult::InvalidCategory;}
	std::string sUserSettingDir = iter_dir->second;
	if(!_pFileParser->OpenFromUserSettingsDir(sUserSettingDir))
	{
		LOG_ERROR_XA_Configuration << "Fail to Get File Content From User Setting Dir [" << sUserSettingDir << "]" << LOG_END;
		return UserConfigurationResult::InvalidFile;
	}

	auto tagItems = _configItems[category];
	for(auto mapIter = tagItems.begin(); mapIter!=tagItems.end(); mapIter++)
	{
		auto config_item=	mapIter->second;
		if(config_item.IsChanged)
		{
std:string itemChildConfigPath=GetElementPath(category,config_item.Tag);
			_pFileParser->SetAttributeStringValue(itemChildConfigPath,VALUE_ATTRIBUTE,config_item.Value);
		}
	}
	if(!_pFileParser->SaveToUserSettingsDir(sUserSettingDir,1))
	{
		LOG_INFO_XA_Configuration << "Invalid Category [" << category << "]" << LOG_END;
		return UserConfigurationResult::Other;
	}

	//TODO: 发送更新通知
	NotifyUserSettingChanged(category);

	return UserConfigurationResult::Ok;
}

std::string XAUserConfiguration::GetElementPath(unsigned category,unsigned tag)
{
	int itemNumber;
	if(!_pFileParser->GetElementNumber(CONFIG_ITEM, &itemNumber))
	{
		LOG_ERROR_XA_Configuration << "Failed to parse category " << CONFIG_ITEM << LOG_END;	
	}

	for(int i=0; i<itemNumber; i++)
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

		istringstream is(id);
		unsigned int categoryid;
		is >> categoryid;
		// TODO: Using boost library

		if(category==categoryid)
		{

			int itemChildNumber;
			std::ostringstream child_index_os;
			child_index_os <<itemConfigPath <<CONFIG_ITEM;
			std::string itemChildIndexConfigPath = child_index_os.str();
			if(!_pFileParser->GetElementNumber(itemChildIndexConfigPath, &itemChildNumber))
			{
				LOG_ERROR_XA_Configuration << "Failed to parse Tag " << itemChildIndexConfigPath << LOG_END;
			}

			std::map<unsigned int, XAUserConfigItem> userConfigItemMap;
			for (int j=0; j<itemChildNumber; j++)
			{
				std::ostringstream childos;
				childos <<itemConfigPath <<CONFIG_ITEM<< "[" << j << "]";
				std::string itemChildConfigPath = childos.str();

				std::string cid;
				if(!_pFileParser->GetAttributeStringValue(itemChildConfigPath, ID_ATTRIBUTE, &cid))
				{
					LOG_ERROR_XA_Configuration << "Failed to Get Attribute [" << ID_ATTRIBUTE  << "] From " << itemChildConfigPath << LOG_END;
					continue;
				}

				istringstream isc(cid);
				unsigned int tagid;
				isc >> tagid;

				if(tag==tagid)
				{
					return itemChildConfigPath;
				}
			}

		}		

	}
	return "";
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

	// Find config item in cache
	auto iterCate =_configItems.find(category);
	if(iterCate == _configItems.end()) 
	{
		LOG_INFO_XA_Configuration << "Invalid Category [" << category << "]" << LOG_END;
		return UserConfigurationResult::InvalidCategory;
	}
	auto iterTag =_configItems[category].find(tag);
	if(iterTag == _configItems[category].end()) 
	{
		LOG_INFO_XA_Configuration << "Invalid Tag [" << tag << "]" << LOG_END;
		return UserConfigurationResult::InvalidTag;
	}

	XAUserConfigItem item= 	_configItems[category][tag];
	item.Value=value;
	item.IsChanged=true;
	_configItems[category][tag]=item;

	//std::string userSettingDir = GetUserSettingDir(category);
	//if(userSettingDir.length() <= 0) {return UserConfigurationResult::InvalidCategory;}
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

void XAUserConfiguration::NotifyUserSettingChanged(unsigned int category)
{
	if(nullptr == _proxy)
	{
		LOG_ERROR_XA_Configuration << "No Communication Proxy to notify user setting changes " << LOG_END;
		return;
	}

	_proxy->SendEvent(_proxy->GetName(), EVENT_ID_USERCONFIGURATION_UPDATED, boost::lexical_cast<std::string>(category));
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
