/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   MirrorObjectCreator
*   Author      :   ÀîÑÇÐÇ
*   Create      :   2013-5-26 13:09
*   LastChange  :   2013-5-26 13:09
*   History     :	
*
*   Description :   MirrorObjectµÄCreator
*
********************************************************************/ 
#ifndef __MIRROROBJECTCREATOR_H__
#define __MIRROROBJECTCREATOR_H__

#include "./MirrorObject.h"

class MirrorObjectCreator
	: public ExtObjCreatorImpl<MirrorObject>
{
public:
	MirrorObjectCreator(void);
	virtual ~MirrorObjectCreator(void);

private:

	virtual MirrorObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(MirrorObject* lpObj);
};

#endif // __MIRROROBJECTCREATOR_H__