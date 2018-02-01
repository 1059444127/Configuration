#pragma once

#ifdef XA_ConfigurationFactory_LIB
#define XA_ConfigurationFactory_Export __declspec (dllexport)
#else //!defined(XA_ConfigurationFactory_LIB)
#define XA_ConfigurationFactory_Export __declspec (dllimport)
#endif