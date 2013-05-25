#include "stdafx.h"
#include "./MagicObjectCreator.h"

MagicObjectCreator::MagicObjectCreator(void)
{
}

MagicObjectCreator::~MagicObjectCreator(void)
{
}

MagicObject* MagicObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(lpObjClass);
	assert(hObj);

	MagicObject* lpExtObj = new MagicObject(hObj);

	return lpExtObj;
}

void MagicObjectCreator::DestroyObj( MagicObject* lpObj )
{
	assert(lpObj);

	delete lpObj;
}