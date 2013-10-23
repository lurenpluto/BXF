/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./NotifyIconObjectParser.h"

NotifyIconObjectParser::NotifyIconObjectParser(void)
{
}

NotifyIconObjectParser::~NotifyIconObjectParser(void)
{
}

bool NotifyIconObjectParser::ParserAttribute( NotifyIconObject* lpObj, const char* key, const char* value )
{
	assert(lpObj);
	assert(key);
	assert(value);

	bool handled = true;

	if (::strcmp(key, "icon") == 0)
	{
		lpObj->SetIconResID(value);
	}
	else if (::strcmp(key, "tip") == 0)
	{
		std::wstring temp;
		XLUETranscode::UTF8_to_Unicode(value, ::strlen(value), temp);

		lpObj->SetTip(temp.c_str());
	}
	else if (::strcmp(key, "iconvisible") == 0)
	{
		bool visible = ::atoi(value)? true : false;
		lpObj->SetIconVisible(visible);
	}
	else
	{
		handled = false;
	}
	
	return handled;
}