#include "stdafx.h"
#include "./RippleObjectRegister.h"
#include "./RippleObjectParser.h"
#include "./RippleObject.h"
#include "./RippleObjectCreator.h"
#include "./LuaRippleObject.h"

BOOL RippleObjectRegister::RegisterRippleObject()
{
	unsigned long attribute = ExtObjAttribute_clipsens;

	return ExtObjRegisterHelper<ExtObjType_renderableObj, RippleObject, RippleObjectCreator, 
		RippleObjectParser, LuaRippleObject>::Register(EXTCLASSNAME_RIPPLEOBJECT, attribute);
}