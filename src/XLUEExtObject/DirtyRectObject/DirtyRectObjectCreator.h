/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   DirtyRectObjectCreator
*   Author      :   李亚星
*   Create      :   2013-9-27 
*   LastChange  :   2013-9-27
*   History     :	
*
*   Description :   DirtyRectObject的创建器
*
********************************************************************/ 
#ifndef __DIRTYRECTOBJECTCREATOR_H__
#define __DIRTYRECTOBJECTCREATOR_H__

#include "./DirtyRectObject.h"

class DirtyRectObjectCreator
	: public ExtObjCreatorImpl<DirtyRectObject>
{
public:
	DirtyRectObjectCreator(void);
	virtual ~DirtyRectObjectCreator(void);

private:

	virtual DirtyRectObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(DirtyRectObject* lpObj);
};

#endif // __DIRTYRECTOBJECTCREATOR_H__