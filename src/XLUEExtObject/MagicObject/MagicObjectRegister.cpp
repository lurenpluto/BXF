#include "stdafx.h"
#include "./MagicObjectRegister.h"
#include "./MagicObject.h"
#include "./MagicObjectCreator.h"
#include "./MagicObjectParser.h"
#include "./LuaMagicObject.h"

BOOL MagicObjectRegister::RegisterMagicObject()
{
	return ExtObjRegisterHelper<ExtObjType_renderableObj, MagicObject, MagicObjectCreator, MagicObjectParser, LuaMagicObject>::Register(EXTCLASSNAME_MAGICOBJECT);
}