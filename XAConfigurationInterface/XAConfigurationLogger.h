#pragma once

#define LOG_END "\n"

#ifndef CONSOLE_LOG
#include "McsfLogger/mcsf_logger.h"

const string XA_Configuration_LOGGER_SOURCE = "XA/Configuration";
const int XA_Configuration_LOGGER_UID = 001035010;

#define LOG_INFO_XA_Configuration             \
	LOG_DEV_INFO_2(            \
	XA_Configuration_LOGGER_SOURCE,  \
	XA_Configuration_LOGGER_UID     \
	)                             

#define LOG_WARN_XA_Configuration              \
	LOG_DEV_WARNING_2(            \
	XA_Configuration_LOGGER_SOURCE,  \
	XA_Configuration_LOGGER_UID     \
	)                             

#define LOG_ERROR_XA_Configuration             \
	LOG_DEV_ERROR_2(                  \
	XA_Configuration_LOGGER_SOURCE,  \
	XA_Configuration_LOGGER_UID     \
	)                               

#define LOG_SVC_ERROR_XA_Configuration             \
	LOG_SVC_ERROR_2(                  \
	XA_Configuration_LOGGER_SOURCE,  \
	XA_Configuration_LOGGER_UID     \
	)                               

#define LOG_SVC_WARN_XA_Configuration             \
	LOG_SVC_WARNING_2(                  \
	XA_Configuration_LOGGER_SOURCE,  \
	XA_Configuration_LOGGER_UID     \
	)                               

#define LOG_SVC_INFO_XA_Configuration             \
	LOG_SVC_INFO_2(                  \
	XA_Configuration_LOGGER_SOURCE,  \
	XA_Configuration_LOGGER_UID     \
	)         

#else

//TODO-RELEASE: Replace CONSOLE LOG with UIH LOG
#include <iostream>

#define LOG_INFO_XA_Configuration  std::cout

#define LOG_WARN_XA_Configuration  std::cout                        

#define LOG_ERROR_XA_Configuration  std::cout                           

#define LOG_SVC_ERROR_XA_Configuration  std::cout                           

#define LOG_SVC_WARN_XA_Configuration  std::cout                           

#define LOG_SVC_INFO_XA_Configuration  std::cout       

#endif

