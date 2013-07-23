/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./BoltBrowserObjectParser.h"

BaseBoltBrowserObjectParser::BaseBoltBrowserObjectParser()
{

}

BaseBoltBrowserObjectParser::~BaseBoltBrowserObjectParser()
{

}

bool BaseBoltBrowserObjectParser::ParserAttribute( BaseBoltBrowserObject* lpBaseObj, const char* key, const char* value )
{
	assert(lpBaseObj);
	assert(key);
	assert(value);

	bool parsered = true;

	if (::strcmp(key, "popupinplace") == 0)
	{
		bool enable = !!::atoi(value);
		lpBaseObj->SetPopupInplace(enable);
	}
	else if (::strcmp(key, "url") == 0)
	{
		std::wstring url;
		XLUETranscode::UTF8_to_Unicode(value, ::strlen(value), url);

		lpBaseObj->Navigate(url.c_str());
	}
	else
	{
		parsered = false;
	}

	return parsered;
}

BoltBrowserObjectParser::BoltBrowserObjectParser(void)
{
}

BoltBrowserObjectParser::~BoltBrowserObjectParser(void)
{
}

bool BoltBrowserObjectParser::ParserAttribute( BoltBrowserObject* lpObj, const char* key, const char* value )
{
	if (BaseBoltBrowserObjectParser::ParserAttribute(lpObj, key, value))
	{
		return true;
	}

	return false;
}

WindowlessBoltBrowserObjectParser::WindowlessBoltBrowserObjectParser( void )
{

}

WindowlessBoltBrowserObjectParser::~WindowlessBoltBrowserObjectParser( void )
{

}

bool WindowlessBoltBrowserObjectParser::ParserAttribute( WindowlessBoltBrowserObject* lpObj, const char* key, const char* value )
{
	if (BaseBoltBrowserObjectParser::ParserAttribute(lpObj, key, value))
	{
		return true;
	}

	bool parsered = true;
	if (::strcmp(key, "transparent") == 0)
	{
		bool enable = !!::atoi(value);
		lpObj->SetTransparnet(enable);
	}
	else
	{
		parsered = false;
	}

	return parsered;
}