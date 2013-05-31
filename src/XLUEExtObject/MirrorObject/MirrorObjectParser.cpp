#include "stdafx.h"
#include "./MirrorObjectParser.h"
#include "./LuaMirrorObject.h"

MirrorObjectParser::MirrorObjectParser(void)
{
}

MirrorObjectParser::~MirrorObjectParser(void)
{
}

BOOL MirrorObjectParser::ParserAttribute( MirrorObject* lpObj, const char* key, const char* value )
{
	assert(lpObj);
	assert(key);
	assert(value);

	BOOL ret = TRUE;
	if (strcmp(key, "mirrortype") == 0)
	{
		MirrorObject::MirrorType type = LuaMirrorObject::GetMirrorTypeFromString(value);
		lpObj->SetMirrorType(type);
	}
	else
	{
		assert(false);
		ret = FALSE;
	}

	return ret;
}