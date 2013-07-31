/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./HostWndIconObjectParser.h"

HostWndIconObjectParser::HostWndIconObjectParser(void)
{
}

HostWndIconObjectParser::~HostWndIconObjectParser(void)
{
}

bool HostWndIconObjectParser::ParserAttribute( HostWndIconObject* lpObj, const char* key, const char* value )
{
	assert(lpObj);
	assert(key);

	bool ret = true;
	if (::strcmp(key, "smallicon") == 0)
	{
		lpObj->SetIconResID(value, false);
	}
	else if (::strcmp(key, "bigicon") == 0)
	{
		lpObj->SetIconResID(value, true);
	}
	else
	{
		assert(false);
		ret = false;
	}

	return ret;
}