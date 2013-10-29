/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./XLUEExtObject.h"
#include <XLUE.h>
#include <assert.h>

#include "./MagicObject/MagicObjectRegister.h"
#include "./MirrorObject/MirrorObjectRegister.h"
#include "./RippleObject/RippleObjectRegister.h"
#include "./IconResource/IconResRegister.h"
#include "./HostWndIconObject/HostWndIconObjectRegister.h"
#include "./RotateObject/RotateObjectRegister.h"
#include "./DirtyRectObject/DirtyRectObjectRegister.h"
#include "./NotifyIconObject/NotifyIconObjectRegister.h"
#include "./GaussianBlurObject/GaussianBlurObjectRegister.h"

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
	XLGraphicPlusParam param;
	XLGP_PrepareGraphicPlusParam(&param);

	param.bInitLua = TRUE;
	XLGP_InitGraphicPlus(&param);

	return TRUE;
}

BOOL XLUE_STDCALL XLUE_UninitExtModule()
{
	XLGP_UnInitGraphicPlus();

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
	else if (strcmp(lpObjClass, EXTCLASSNAME_HOSTWNDICONOBJECT) == 0)
	{
		ret = HostWndIconObjectRegister::RegisterHostWndIconObject();
	}
	else if (strcmp(lpObjClass, EXTCLASSNAME_ROTATEOBJECT) == 0)
	{
		ret = RotateObjectRegister::RegisterRotateObject();
	}
	else if (strcmp(lpObjClass, EXTCLASSNAME_DIRTYRECTOBJECT) == 0)
	{
		ret = DirtyRectObjectRegister::RegisterDirtyRectObject();
	}
	else if (strcmp(lpObjClass, EXTCLASSNAME_NOTIFYICONOBJECT) == 0)
	{
		ret = NotifyIconObjectRegister::RegisterNotifyIconObject();
	}
	else if (strcmp(lpObjClass, EXTCLASSNAME_GAUSSIANBLUROBJECT) == 0)
	{
		ret = GaussianBlurObjectRegister::RegisterGaussianBlurObject();
	}
	else
	{
		assert(false);
	}

	return ret;
}

BOOL XLUE_STDCALL XLUE_RegisterRes( const char* lpCategory, const char* lpResClass )
{
	assert(lpCategory);
	assert(lpResClass);

	bool ret = false;

	if (strcmp(lpResClass, XLUE_EXTRES_ICON) == 0)
	{
		ret = IconResRegister::RegisterIconRes();
	}
	else
	{
		assert(false);
	}

	return ret? TRUE : FALSE;
}