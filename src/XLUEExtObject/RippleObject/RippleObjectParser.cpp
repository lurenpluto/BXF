/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./RippleObjectParser.h"

RippleObjectParser::RippleObjectParser(void)
{
}

RippleObjectParser::~RippleObjectParser(void)
{
}

bool RippleObjectParser::ParserAttribute( RippleObject* lpObj, const char* key, const char* value )
{
	bool ret = true;

	assert(lpObj);
	if (strcmp(key, "mousedrop") == 0)
	{
		bool enable = ::atoi(value)? true : false;
		lpObj->SetMouseDrop(enable);
	}
	else if (strcmp(key, "randomdrop") == 0)
	{
		bool enable = ::atoi(value)? true : false;
		lpObj->SetRandomDrop(enable);
	}
	else if (strcmp(key, "dropdensity") == 0)
	{
		unsigned long density = (unsigned long)::atoi(value);
		lpObj->SetDropDensity(density);
	}
	else if (strcmp(key, "updateinterval") == 0)
	{
		unsigned long interval = (unsigned long)::atoi(value);
		lpObj->SetUpdateInterval(interval);
	}
	else if (strcmp(key, "waterdensity") == 0)
	{
		unsigned long density = (unsigned long)::atoi(value);
		lpObj->SetWaterDensity(density);
	}
	else
	{
		ret = false;
		assert(false);
	}

	return ret;
}