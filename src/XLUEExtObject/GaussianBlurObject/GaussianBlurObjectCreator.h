/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#ifndef __GAUSSIANBLUROBJECTCREATOR_H__
#define __GAUSSIANBLUROBJECTCREATOR_H__

#include "./GaussianBlurObject.h"

class GaussianBlurObjectCreator
	: public ExtObjCreatorImpl<GaussianBlurObject>
{
public:
	GaussianBlurObjectCreator(void);
	virtual ~GaussianBlurObjectCreator(void);

private:

	virtual GaussianBlurObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(GaussianBlurObject* lpObj);
};

#endif // __GAUSSIANBLUROBJECTCREATOR_H__