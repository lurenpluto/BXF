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