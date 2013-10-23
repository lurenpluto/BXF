/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#ifndef __SVGOBJECTCREATOR_H__
#define __SVGOBJECTCREATOR_H__

#include "./SvgObject.h"

class SvgObjectCreator
	: public ExtObjCreatorImpl<SvgObject>
{
public:
	SvgObjectCreator(void);
	virtual ~SvgObjectCreator(void);

private:

	virtual SvgObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(SvgObject* lpObj);
};

#endif // __SVGOBJECTCREATOR_H__