/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./SvgObjectParser.h"
#include "./LuaSvgObject.h"

SvgObjectParser::SvgObjectParser(void)
{
}

SvgObjectParser::~SvgObjectParser(void)
{
}

bool SvgObjectParser::ParserAttribute( SvgObject* lpObj, const char* key, const char* value )
{
	assert(lpObj);
	assert(key);
	assert(value);

	bool ret = true;
	if (strcmp(key, "svgres") == 0)
	{
		lpObj->SetSvgResID(value);
	}
    else if (strcmp(key, "preserveAspectRatio") == 0)
    {
        if (strcmp(value, "true") == 0)
        {
            lpObj->SetPreserveAspectRatio(true);
        }
        else
        {
            lpObj->SetPreserveAspectRatio(false);
        }
    }
    else if (strcmp(key, "enableAlpha") == 0)
    {
        if (strcmp(value, "false") == 0)
        {
            lpObj->SetEnableSvgAlpha(false);
        }
        else
        {
            lpObj->SetEnableSvgAlpha(true);
        }
    }
	else
	{
		assert(false);
		ret = false;
	}

	return ret;
}