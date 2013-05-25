/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   MagicObjectCreator
*   Author      :   李亚星
*   Create      :   2013-5-20 0:28
*   LastChange  :   2013-5-20 0:28
*   History     :	
*
*   Description :   MagicObject的创建管理器
*
********************************************************************/ 
#ifndef __MAGICOBJECTCREATOR_H__
#define __MAGICOBJECTCREATOR_H__

#include "./MagicObject.h"

class MagicObjectCreator
	: public ExtObjCreatorImpl<MagicObject>
{
public:
	MagicObjectCreator(void);
	virtual ~MagicObjectCreator(void);

private:

	virtual MagicObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(MagicObject* lpObj);
};

#endif // __MAGICOBJECTCREATOR_H__