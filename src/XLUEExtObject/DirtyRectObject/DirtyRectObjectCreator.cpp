#include "stdafx.h"
#include "./DirtyRectObjectCreator.h"
#include "./DirtyRectObject.h"

DirtyRectObjectCreator::DirtyRectObjectCreator(void)
{
}

DirtyRectObjectCreator::~DirtyRectObjectCreator(void)
{
}

DirtyRectObject* DirtyRectObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(lpObjClass);
	assert(hObj);

	return new DirtyRectObject(hObj);
}

void DirtyRectObjectCreator::DestroyObj( DirtyRectObject* lpObj )
{
	assert(lpObj);

	delete lpObj;
}