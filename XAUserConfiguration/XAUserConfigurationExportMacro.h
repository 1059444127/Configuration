#pragma once

#ifdef XA_UserConfiguration_LIB
#define XA_UserConfiguration_Export __declspec (dllexport)
#else //!defined(XA_UserConfiguration_LIB)
#define XA_UserConfiguration_Export __declspec (dllimport)
#endif