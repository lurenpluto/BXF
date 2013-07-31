/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./IconResCreator.h"

IconResCreator::IconResCreator(void)
{
}

IconResCreator::~IconResCreator(void)
{
}

IconRes* IconResCreator::CreateResource( const char* lpResType, XLUE_RESOURCE_HANDLE hResHandle )
{
	assert(lpResType);
	assert(strcmp(XLUE_EXTRES_ICON, lpResType) == 0);
	assert(hResHandle);

	IconRes* lpResObj = new IconRes(hResHandle);

	return lpResObj;
}

void IconResCreator::DestroyResource( IconRes* lpResObj )
{
	assert(lpResObj);

	delete lpResObj;
}