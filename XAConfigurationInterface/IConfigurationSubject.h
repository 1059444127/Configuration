#pragma once
#include "XAConfigurationMacro.h"
#include "XAConfigurationLogger.h"
#include <list>
#include "IConfigurationObserver.h"

class IConfigurationSubject
{
public:
	virtual void NotifyObservers(unsigned int category)
	{
		LOG_INFO_XA_Configuration << "Notify Category [" << category << "] changed" << LOG_END;
		for (auto iter = _observers.begin(); iter != _observers.end(); iter++)
		{
			(*iter)->UpdateConfiguration(category);
		}
	}

	void RegisterObserver(IConfigurationObserver *pConfigurationObserver)
	{
		LOG_INFO_XA_Configuration << "Regiter an Observer" << LOG_END;
		_observers.push_back(pConfigurationObserver);
	}

	void RemoveObserver(IConfigurationObserver *pConfigurationObserver)
	{
		LOG_INFO_XA_Configuration << "Remove an Observer" << LOG_END;
		_observers.remove(pConfigurationObserver);
	}

	virtual ~IConfigurationSubject() {_observers.clear();}
private:
	std::list<IConfigurationObserver*> _observers; 
	XA_Configuration_DISALLOW_COPY_AND_ASSIGN(IConfigurationSubject)
};
