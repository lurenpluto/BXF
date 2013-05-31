#include "stdafx.h"
#include "./MirrorObjectCreator.h"

MirrorObjectCreator::MirrorObjectCreator(void)
{
}

MirrorObjectCreator::~MirrorObjectCreator(void)
{
}

MirrorObject* MirrorObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(hObj);
	assert(lpObjClass);

	return new MirrorObject(hObj);
}

void MirrorObjectCreator::DestroyObj( MirrorObject* lpObj )
{
	assert(lpObj);

	delete lpObj;
}