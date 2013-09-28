#include "stdafx.h"
#include "./DirtyRectObjectRegister.h"
#include "./DirtyRectObjectCreator.h"
#include "./DirtyRectObjectParser.h"

bool DirtyRectObjectRegister::RegisterDirtyRectObject()
{
	return ExtObjRegisterHelper<ExtObjType_layoutObj, DirtyRectObject, DirtyRectObjectCreator, 
		DirtyRectObjectParser>::Register(EXTCLASSNAME_DIRTYRECTOBJECT, 0);
}