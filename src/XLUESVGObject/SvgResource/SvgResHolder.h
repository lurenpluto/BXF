/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 

#ifndef __SVGRESHOLDER_H__
#define __SVGRESHOLDER_H__

#include "./SvgRes.h"

class SVGResTraits
    : public ExtResTraits<SVGResTraits>
{
public:

    static const char* GetResType()
    {
        return XLUE_EXTRES_SVG;
    }
};

typedef BaseResHolder<SVGResTraits> SVGResHolder;

#endif // __ICONRESHOLDER_H__