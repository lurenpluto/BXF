/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#ifndef __SVGOBJECT_H__
#define __SVGOBJECT_H__

#include "../SvgResource/SvgResHolder.h"

class SvgObject
	: public ExtLayoutObjMethodsImpl
{
public:
    typedef BaseResHolderEx<SvgObject, SvgResTraits> SvgResHolderEx;
public:

	SvgObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~SvgObject(void);

	void SetSvgResID(const char* resID);
	const char* GetSvgResID() const;

    void SetPreserveAspectRatio(bool preserveAspectRatio);
    bool GetPreserveAspectRatio();

    void SetEnableSvgAlpha(bool enableSvgAlpha);
    bool GetEnableSvgAlpha();

    void SetSvgRes(XLUE_RESOURCE_HANDLE hResHandle);
    // 返回值不增持引用计数
    XLUE_RESOURCE_HANDLE GetSvgRes();

public:

	// ExtLayoutObjMethodsImpl virtual funtions

	// 该对象是剪裁敏感的，所以需要配合LayerObject+clipsens使用
	virtual void OnPaintEx(XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char alpha, XLGraphicHint* lpHint);

private:
    void OnSvgResChange();

    SvgResHolderEx m_SvgRes;
    bool m_preserveAspectRatio;
    bool m_enableSvgAlpha;
};

#endif // __SVGOBJECT_H__