/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#ifndef __SVGOBJECTCREATOR_H__
#define __SVGOBJECTCREATOR_H__

#include "./SvgObject.h"

class SVGObjectCreator
	: public ExtObjCreatorImpl<SVGObject>
{
public:
	SVGObjectCreator(void);
	virtual ~SVGObjectCreator(void);

private:

	virtual SVGObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(SVGObject* lpObj);
};

#endif // __SVGOBJECTCREATOR_H__