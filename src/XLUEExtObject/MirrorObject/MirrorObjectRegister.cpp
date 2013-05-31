#include "stdafx.h"
#include "./MirrorObjectRegister.h"
#include "./MirrorObject.h"
#include "./MirrorObjectCreator.h"
#include "./MirrorObjectParser.h"
#include "./LuaMirrorObject.h"

BOOL MirrorObjectRegister::RegisterMirrorObject()
{
	unsigned long attribute = ExtObjAttribute_clipsens;

	return ExtObjRegisterHelper<ExtObjType_renderableObj, MirrorObject, MirrorObjectCreator, 
		MirrorObjectParser, LuaMirrorObject>::Register(EXTCLASSNAME_MIRROROBJECT, attribute);
}