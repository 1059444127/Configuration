#include <iostream>
#include "XAConfiguration/XAConfigurationFactory.h"
using namespace std;

static int main()
{
	auto configurationFactory = XAConfigurationFactory::Instance();
	IUserConfiguration* userConfiguration = configurationFactory->GetUserConfiguration();

	cin.get();

	userConfiguration->LoadUserConfig(11);

	cin.get();
	return 0;
}