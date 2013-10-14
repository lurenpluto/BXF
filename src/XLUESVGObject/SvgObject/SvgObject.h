/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#ifndef __SVGOBJECT_H__
#define __SVGOBJECT_H__

#include "../SvgResource/SvgResHolder.h"

class SVGObject
	: public ExtLayoutObjMethodsImpl
{
public:
    typedef BaseResHolderEx<SVGObject, SVGResTraits> SVGResHolderEx;
public:

	SVGObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~SVGObject(void);

	void SetSVGResID(const char* resID);
	const char* GetSVGResID() const;

    void SetPreserveAspectRatio(bool preserveAspectRatio);
    bool GetPreserveAspectRatio();

    void SetEnableSVGAlpha(bool enableSVGAlpha);
    bool GetEnableSVGAlpha();

    void SetSVGRes(XLUE_RESOURCE_HANDLE hResHandle);
    // 返回值不增持引用计数
    XLUE_RESOURCE_HANDLE GetSVGRes();

public:

	// ExtLayoutObjMethodsImpl virtual funtions

	virtual void OnPaintEx(XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char alpha, XLGraphicHint* lpHint);
    virtual void OnAbsPosChanged(const RECT* lpOldAbsPos, const RECT* lpNewAbsPos);

private:
    void OnSVGResChange();

private:

    SVGResHolderEx m_SVGRes;
    bool m_preserveAspectRatio;
    bool m_enableSVGAlpha;

    wxImage m_imageCache;
    bool m_isDirty;
    int m_objWidth;
    int m_objHeight;
};

#endif // __SVGOBJECT_H__