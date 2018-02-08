#include <iostream>
#include "XAConfiguration/XAConfigurationFactory.h"
using namespace std;

static int main()
{
	auto configurationFactory = XAConfigurationFactory::Instance();
	IUserConfiguration* userConfiguration = configurationFactory->GetUserConfiguration();

	//Configuration Properties =>   Debugging =>  Working Directory =>  $(OutDir)

	userConfiguration->LoadUserConfig(11);

	userConfiguration->SetUserConfig(11,1102,"202");
	userConfiguration->SetUserConfig(11,1103,"false");

	userConfiguration->SaveUserConfig(11);

	cin.get();
	return 0;
}