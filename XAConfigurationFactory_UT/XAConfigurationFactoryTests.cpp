#include "XAConfigurationFactoryTests.h"
#include "XAConfiguration/XAConfigurationFactory.h"

TEST_F(XAConfigurationFactoryTests, XAConfigurationFactory_Is_Singleton)
{
	auto pConfigurationFactory1 = XAConfigurationFactory::Instance();
	auto pConfigurationFactory2 = XAConfigurationFactory::Instance();
	
	EXPECT_TRUE(pConfigurationFactory1==pConfigurationFactory2);
}