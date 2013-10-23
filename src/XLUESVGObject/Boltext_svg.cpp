/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 

#include "stdafx.h"
#include "Boltext_svg.h"

#include "./SvgResource/SvgResRegister.h"
#include "./SvgObject/SvgObjectRegister.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
                      )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// 扩展模块初始回调，每个扩展模块被加载时候会调用该接口
BOOL XLUE_STDCALL XLUE_InitExtModule()
{
    return TRUE;
}

BOOL XLUE_STDCALL XLUE_UninitExtModule()
{
    return TRUE;
}

BOOL XLUE_STDCALL XLUE_RegisterObj( const char* lpCategory, const char* lpObjClass )
{
    assert(lpCategory);
    assert(lpObjClass);

    BOOL ret = FALSE;

    if (strcmp(lpObjClass, EXTCLASSNAME_SVGOBJECT) == 0)
    {
        ret = SVGObjectRegister::RegisterSVGObject();
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

    if (strcmp(lpResClass, XLUE_EXTRES_SVG) == 0)
    {
        ret = SVGResRegister::RegisterSVGRes();
    }
    else
    {
        assert(false);
    }

    return ret? TRUE : FALSE;
}
