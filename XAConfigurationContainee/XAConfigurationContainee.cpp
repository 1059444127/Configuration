#include "XAConfigurationContainee.h"
#include <iostream>
#include "XAConfiguration/XAConfigurationFactory.h"

IMPLEMENT_CONTAINEE(XAConfigurationContainee);

void XAConfigurationContainee::Startup()
{
}

void XAConfigurationContainee::DoWork()
{
	std::cin.get();
	auto configurationFactory = XAConfigurationFactory::Instance();
	IUserConfiguration* userConfiguration = configurationFactory->GetUserConfiguration();
	userConfiguration->SetCommunicationProxy(m_pCommunicationProxy);
	userConfiguration->LoadUserConfig(11);

	userConfiguration->SetUserConfig(11,1102,"202");
	userConfiguration->SetUserConfig(11,1103,"false");

	userConfiguration->SaveUserConfig(11);
	std::cin.get();
}

void XAConfigurationContainee::SetCommunicationProxy(Mcsf::ICommunicationProxy* pProxy)
{
	m_pCommunicationProxy = pProxy;
}