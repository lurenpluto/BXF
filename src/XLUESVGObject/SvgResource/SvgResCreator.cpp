/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./SvgResCreator.h"

SVGResCreator::SVGResCreator(void)
{
}

SVGResCreator::~SVGResCreator(void)
{
}

SVGRes* SVGResCreator::CreateResource( const char* lpResType, XLUE_RESOURCE_HANDLE hResHandle )
{
    assert(lpResType);
    assert(strcmp(XLUE_EXTRES_SVG, lpResType) == 0);
    assert(hResHandle);

    SVGRes* lpResObj = new SVGRes(hResHandle);

    return lpResObj;
}

void SVGResCreator::DestroyResource( SVGRes* lpResObj )
{
    assert(lpResObj);

    delete lpResObj;
}