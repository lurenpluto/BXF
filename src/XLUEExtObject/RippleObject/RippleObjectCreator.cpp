#include "stdafx.h"
#include "./RippleObjectCreator.h"

RippleObjectCreator::RippleObjectCreator(void)
{
}

RippleObjectCreator::~RippleObjectCreator(void)
{
}

RippleObject* RippleObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(lpObjClass);
	assert(hObj);

	return new RippleObject(hObj);
}

void RippleObjectCreator::DestroyObj( RippleObject* lpObj )
{
	assert(lpObj);

	delete lpObj;
}