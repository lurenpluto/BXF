// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the XLUEEXTOBJECT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// XLUEEXTOBJECT_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef XLUEEXTOBJECT_EXPORTS
#define XLUEEXTOBJECT_API __declspec(dllexport)
#else
#define XLUEEXTOBJECT_API __declspec(dllimport)
#endif

#include <XLUE.h>

BOOL XLUE_STDCALL XLUE_ExtObj_RegisterObj(const char* lpObjClass);