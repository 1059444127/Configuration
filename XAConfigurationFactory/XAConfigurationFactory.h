#pragma once

#include "XAConfigurationFactoryExportMacro.h"
#include "XAConfiguration/XAConfigurationMacro.h"

class XA_ConfigurationFactory_Export XAConfigurationFactory
{
public:
	static XAConfigurationFactory* Instance();
	~XAConfigurationFactory();

private:
	static XAConfigurationFactory * _pInstance;
	XAConfigurationFactory() {};
	XA_Configuration_DISALLOW_COPY_AND_ASSIGN(XAConfigurationFactory)
};