#pragma once

#define USER_CONFIG_PATH "UserConfigPath"
#define CONFIG_INDEX_FILE "ConfigIndex.xml"
#define CONFIG_ITEM "/Item"
#define ID_ATTRIBUTE "id"
#define NAME_ATTRIBUTE "name"
#define LOCATION_ATTRIBUTE "location"
#define XA_CONFIGURATION_EMPTY_STRING ""


#define XA_Configuration_DISALLOW_COPY(classname) \
    classname(const classname & );
#define XA_Configuration_DISALLOW_ASSIGN(classname) \
    void operator = (const classname & );
#define XA_Configuration_DISALLOW_COPY_AND_ASSIGN(classname) \
    XA_Configuration_DISALLOW_COPY  (classname)\
    XA_Configuration_DISALLOW_ASSIGN(classname)

#ifndef SAFE_DELETE_ELEMENT
#define SAFE_DELETE_ELEMENT(ptr) {\
if (ptr != nullptr)\
{\
delete ptr;\
ptr = nullptr;\
}\
}
#endif