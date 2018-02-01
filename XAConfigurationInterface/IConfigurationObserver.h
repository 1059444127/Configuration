#pragma once
class IConfigurationObserver
{
public:
	virtual void UpdateConfiguration(unsigned int category) = 0;
	virtual ~IConfigurationObserver() {}
};