/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./RotateObjectParser.h"
#include "./LuaRotateObject.h"

RotateObjectParser::RotateObjectParser(void)
{
}

RotateObjectParser::~RotateObjectParser(void)
{
}

bool RotateObjectParser::ParserAttribute( RotateObject* lpObj, const char* key, const char* value )
{
	assert(lpObj);
	assert(key);
	assert(value);

	bool ret = true;
	if (::strcmp(key, "angel") == 0)
	{
		lpObj->SetAngel(::atof(value));
	}
	else if (::strcmp(key, "centerx") == 0)
	{
		lpObj->SetStringX(value);
	}
	else if (::strcmp(key, "centery") == 0)
	{
		lpObj->SetStringY(value);
	}
	else if (::strcmp(key, "rotatemode") == 0)
	{
		lpObj->SetRotateMode(LuaRotateObject::GetRotateModeFromString(value));
	}
	else
	{
		ret = false;
	}

	return ret;
}