#pragma once

#include "McsfContainee\mcsf_containee_base.h"
#include "XAConfiguration\XAConfigurationMacro.h"

class ICommunicationProxy;
class IEventHandler;
class ICommandHandler;
class IBigDataHandler;


class XAConfigurationContainee : public Mcsf::IContainee
{
public:


	XAConfigurationContainee(): m_pCommunicationProxy(nullptr)
	{
	}

	/**
	 * \brief Containee Startup
	 */
	void Startup() ;
	/**
	 * \brief Containee DoWork
	 */
	void DoWork() ;
	/**
	 * \brief Containee Shutdown
	 * \param bReboot if reboot or not
	 * \return ?
	 */
	bool Shutdown(bool bReboot) {return true;}
	///**
	// * \brief 
	// * \param pProxy CommunicationProxy Created by Container
	// */
	void SetCommunicationProxy(Mcsf::ICommunicationProxy* pProxy) ;
	/**
	 * \brief Estimate time to finish job for waiting system manager
	 * \param bReboot if reboot or not
	 * \return time left to finish job , unit: ms
	 */
	virtual int GetEstimatedTimeToFinishJob(bool bReboot) { return 0;}

	virtual void SetCustomConfigFile(const std::string& sFilename) { sFilename;}
	virtual std::list<std::string> GetRunningTasks() {return std::list<std::string>();}
	virtual void StartShutdown(bool bReboot) {bReboot;}
	virtual int GetTaskRemainingProgress(std::list<Mcsf::TaskProgress>& taskProgress) {return 0;}
	virtual ~XAConfigurationContainee() {}

private:
	XA_Configuration_DISALLOW_COPY_AND_ASSIGN(XAConfigurationContainee);
	Mcsf::ICommunicationProxy * m_pCommunicationProxy;
};

DECLARE_CONTAINEE(XAConfigurationContainee);
