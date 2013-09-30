/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./SvgResCreator.h"

SvgResCreator::SvgResCreator(void)
{
}

SvgResCreator::~SvgResCreator(void)
{
}

SvgRes* SvgResCreator::CreateResource( const char* lpResType, XLUE_RESOURCE_HANDLE hResHandle )
{
    assert(lpResType);
    assert(strcmp(XLUE_EXTRES_SVG, lpResType) == 0);
    assert(hResHandle);

    SvgRes* lpResObj = new SvgRes(hResHandle);

    return lpResObj;
}

void SvgResCreator::DestroyResource( SvgRes* lpResObj )
{
    assert(lpResObj);

    delete lpResObj;
}