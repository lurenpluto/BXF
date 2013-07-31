/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./MagicObjectParser.h"

MagicObjectParser::MagicObjectParser(void)
{
}

MagicObjectParser::~MagicObjectParser(void)
{
}

bool MagicObjectParser::ParserAttribute( MagicObject* lpObj, const char* /*key*/, const char* /*value*/ )
{
	assert(lpObj);

	return false;
}