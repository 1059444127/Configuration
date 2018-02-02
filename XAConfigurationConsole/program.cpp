#include <iostream>
#include "XAConfiguration/XAConfigurationFactory.h"
using namespace std;

static int main()
{
	auto configurationFactory = XAConfigurationFactory::Instance();
	IUserConfiguration* userConfiguration = configurationFactory->GetUserConfiguration();

	cin.get();
	return 0;
}