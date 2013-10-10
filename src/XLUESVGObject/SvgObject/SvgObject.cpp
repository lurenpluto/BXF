/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./SvgObject.h"
#include "svg/wxImage.h"

SVGObject::SVGObject( XLUE_LAYOUTOBJ_HANDLE hObj )
:ExtLayoutObjMethodsImpl(hObj)
, m_preserveAspectRatio(false)
, m_enableSVGAlpha(true)
, m_isDirty(true)
, m_destWidth(0)
, m_destHeight(0)
{
    m_SVGRes.SetOwner(this);
    m_SVGRes.SetResFunc(&SVGObject::OnSVGResChange, NULL);

    m_SVGRes.SetResProvider(GetResProvider());

    RECT initRect = {0};
    m_srcRect = initRect;
}

SVGObject::~SVGObject(void)
{
}

void SVGObject::SetSVGResID( const char* resID)
{
    m_SVGRes.SetResID(resID);
}

const char* SVGObject::GetSVGResID() const
{
    return m_SVGRes.GetID();
}

void SVGObject::SetEnableSVGAlpha(bool enableSVGAlpha)
{
    m_enableSVGAlpha = enableSVGAlpha;
    m_isDirty = true;
}

bool SVGObject::GetEnableSVGAlpha()
{
    return m_enableSVGAlpha;
}

void SVGObject::SetPreserveAspectRatio(bool preserveAspectRatio)
{
    m_preserveAspectRatio = preserveAspectRatio;
    m_isDirty = true;
}

bool SVGObject::GetPreserveAspectRatio()
{
    return m_preserveAspectRatio;
}

void SVGObject::SetSVGRes( XLUE_RESOURCE_HANDLE hResHandle)
{
    m_SVGRes.SetHandle(hResHandle);
}

XLUE_RESOURCE_HANDLE SVGObject::GetSVGRes()
{
    XLUE_RESOURCE_HANDLE hResHandle = NULL;
    hResHandle = m_SVGRes.GetHandle();

    return hResHandle;
}

void SVGObject::OnSVGResChange()
{
    //资源改变时要重新绘制
    m_isDirty = true;
}

void SVGObject::OnPaintEx( XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char alpha, XLGraphicHint* lpHint )
{
	assert(lpSrcClipRect);

	XL_BITMAP_HANDLE hClipBitmap = XL_ClipSubBindBitmap(hBitmapDest, lpDestClipRect);
	assert(hClipBitmap);

    XLUE_RESOURCE_HANDLE hRes = NULL;
    hRes = m_SVGRes.GetHandle();
    wxSVGDocument* pSVGDoc = (wxSVGDocument*)XLUE_GetResRealHandle(hRes);
    assert(pSVGDoc);

    wxSVGRect srcRect;
    srcRect.SetX(lpSrcClipRect->left);
    srcRect.SetY(lpSrcClipRect->top);
    srcRect.SetWidth(lpSrcClipRect->right - lpSrcClipRect->left);
    srcRect.SetHeight(lpSrcClipRect->bottom - lpSrcClipRect->top);

    //当目标区域改变大小，或者源区域改变位置的时候，也要重新绘制
    if (m_destWidth != lpDestClipRect->right-lpDestClipRect->left
        || m_destHeight != lpDestClipRect->bottom-lpDestClipRect->top
        || !RectHelper::EqualRect(&m_srcRect, lpSrcClipRect))
    {
        m_isDirty = true;
        m_destWidth = lpDestClipRect->right-lpDestClipRect->left;
        m_destHeight = m_destHeight != lpDestClipRect->bottom-lpDestClipRect->top;
        m_srcRect = *lpSrcClipRect;
    }

    if (m_isDirty)
    {
        m_imageCache = pSVGDoc->Render(lpDestClipRect->right-lpDestClipRect->left
            , lpDestClipRect->bottom-lpDestClipRect->top
            , &srcRect, m_preserveAspectRatio, m_enableSVGAlpha);
        m_isDirty = false;
    }

    XL_BITMAP_HANDLE hRendedBitmap = m_imageCache.GetXLBitmapHandle();

    XLBlendHint hint;
    hint.BaseHint = *lpHint;
    hint.ConstAlpha = alpha;
    hint.BlendType = XLGRAPHIC_BLEND_SRC_ALPHA;

    XL_Blend(hClipBitmap, lpDestClipRect->left, lpDestClipRect->top, hRendedBitmap, &hint);

	XL_ReleaseBitmap(hClipBitmap);
}