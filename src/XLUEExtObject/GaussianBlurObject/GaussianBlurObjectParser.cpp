/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./GaussianBlurObjectParser.h"
#include "./LuaGaussianBlurObject.h"

GaussianBlurObjectParser::GaussianBlurObjectParser(void)
{
}

GaussianBlurObjectParser::~GaussianBlurObjectParser(void)
{
}

bool GaussianBlurObjectParser::ParserAttribute( GaussianBlurObject* lpObj, const char* key, const char* value )
{
	assert(lpObj);
	assert(key);
	assert(value);

	bool ret = true;
	
	if (strcmp(key, "sigma") == 0)
	{
		float sigma = LuaGaussianBlurObject::GetSigmaFromString(value);
		lpObj->SetSigma(sigma);
	}
	else if (strcmp(key, "radius" )== 0)
	{
		int radius = atoi(value);
		lpObj->SetRadius(radius);
	}
	else if(strcmp(key, "gaussiantype") == 0)
	{
		lpObj->SetGaussianType(value);
	}
	else
	{
		assert(false);
		ret = false;
	}

	return ret;
}