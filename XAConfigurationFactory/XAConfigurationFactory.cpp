#include "XAConfigurationFactory.h"
#include <boost/thread/mutex.hpp>
#include "XAConfiguration/XAConfigurationLogger.h"
#include "XAUserConfiguration.h"

XAConfigurationFactory* XAConfigurationFactory::_pInstance;
boost::mutex XA_Configuration_Mutex;

XAConfigurationFactory* XAConfigurationFactory::Instance()
{
	if(nullptr == _pInstance)
	{
		boost::mutex::scoped_lock(XA_Configuration_Mutex);
		if(nullptr == _pInstance)
		{
			_pInstance = new XAConfigurationFactory();
			LOG_INFO_XA_Configuration << "XAConfigurationFactory Initialized" << LOG_END ;
		}
	}

	return _pInstance;
}

XAConfigurationFactory::~XAConfigurationFactory()
{
	SAFE_DELETE_ELEMENT(_pInstance);
}

IUserConfiguration* XAConfigurationFactory::CreateUserConfiguration()
{
	return new XAUserConfiguration();
}
