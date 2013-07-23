// XLUEExtObject.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "./XLUEExtObject.h"
#include <XLUE.h>
#include <assert.h>

#include "./MagicObject/MagicObjectRegister.h"
#include "./MirrorObject/MirrorObjectRegister.h"
#include "./RippleObject/RippleObjectRegister.h"


BOOL APIENTRY DllMain( HANDLE /*hModule*/, 
                       DWORD  /*ul_reason_for_call*/, 
                       LPVOID /*lpReserved*/
					 )
{
    return TRUE;
}

// 扩展模块初始回调，每个扩展模块被加载时候会调用该接口
BOOL XLUE_STDCALL XLUE_InitExtModule()
{
	//TODO
	return TRUE;
}

BOOL XLUE_STDCALL XLUE_UninitExtModule()
{
	//TODO
	return TRUE;
}

BOOL XLUE_STDCALL XLUE_RegisterObj( const char* lpCategory, const char* lpObjClass )
{
	assert(lpCategory);
	assert(lpObjClass);

	BOOL ret = FALSE;

	if (strcmp(lpObjClass, EXTCLASSNAME_MAGICOBJECT) == 0)
	{
		ret = MagicObjectRegister::RegisterMagicObject();
	}
	else if (strcmp(lpObjClass, EXTCLASSNAME_MIRROROBJECT) == 0)
	{
		ret = MirrorObjectRegister::RegisterMirrorObject();
	}
	else if (strcmp(lpObjClass, EXTCLASSNAME_RIPPLEOBJECT) == 0)
	{
		ret = RippleObjectRegister::RegisterRippleObject();
	}
	else
	{
		assert(false);
	}

	return ret;
}