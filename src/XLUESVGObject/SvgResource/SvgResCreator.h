/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 

#ifndef __SVGRESCREATOR_H__
#define __SVGRESCREATOR_H__

#include "./SvgRes.h"

class SVGResCreator
    : public ExtResourceCreatorImpl<SVGRes>
{
public:
    SVGResCreator(void);
    virtual ~SVGResCreator(void);

private:

    // ExtResourceCreatorImpl
    virtual SVGRes* CreateResource(const char* lpResType, XLUE_RESOURCE_HANDLE hResHandle);
    virtual void DestroyResource(SVGRes* lpResObj);
};

#endif // __ICONRESCREATOR_H__