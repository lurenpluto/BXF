/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./DirtyRectObjectParser.h"

DirtyRectObjectParser::DirtyRectObjectParser(void)
{
}

DirtyRectObjectParser::~DirtyRectObjectParser(void)
{
}

bool DirtyRectObjectParser::ParserAttribute( DirtyRectObject* lpObj, const char* key, const char* value )
{
	assert(lpObj);
	assert(key);
	assert(value);

	bool handled = true;

	if (::strcmp(key, "geninterval") == 0)
	{
		unsigned int interval = static_cast<unsigned int>(::atoi(value));
		lpObj->SetGenInterval(interval);
	}
	else
	{
		handled = false;
	}

	return handled;
}