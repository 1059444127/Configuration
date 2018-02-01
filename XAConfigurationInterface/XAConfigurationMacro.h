#pragma once

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