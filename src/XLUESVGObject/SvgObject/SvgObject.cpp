/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./SvgObject.h"
#include "svg/wxImage.h"

SvgObject::SvgObject( XLUE_LAYOUTOBJ_HANDLE hObj )
:ExtLayoutObjMethodsImpl(hObj)
, m_preserveAspectRatio(false)
, m_enableSvgAlpha(true)
{
    m_SvgRes.SetOwner(this);
    m_SvgRes.SetResFunc(&SvgObject::OnSvgResChange, NULL);

    m_SvgRes.SetResProvider(GetResProvider());
}

SvgObject::~SvgObject(void)
{
}

void SvgObject::SetSvgResID( const char* resID)
{
    m_SvgRes.SetResID(resID);
}

const char* SvgObject::GetSvgResID() const
{
    return m_SvgRes.GetID();
}

void SvgObject::SetEnableSvgAlpha(bool enableSvgAlpha)
{
    m_enableSvgAlpha = enableSvgAlpha;
}

bool SvgObject::GetEnableSvgAlpha()
{
    return m_enableSvgAlpha;
}

void SvgObject::SetPreserveAspectRatio(bool preserveAspectRatio)
{
    m_preserveAspectRatio = preserveAspectRatio;
}

bool SvgObject::GetPreserveAspectRatio()
{
    return m_preserveAspectRatio;
}

void SvgObject::SetSvgRes( XLUE_RESOURCE_HANDLE hResHandle)
{
    m_SvgRes.SetHandle(hResHandle);
}

XLUE_RESOURCE_HANDLE SvgObject::GetSvgRes()
{
    XLUE_RESOURCE_HANDLE hResHandle = NULL;
    hResHandle = m_SvgRes.GetHandle();

    return hResHandle;
}

void SvgObject::OnSvgResChange()
{
    
}

void SvgObject::OnPaintEx( XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char alpha, XLGraphicHint* lpHint )
{
	assert(lpSrcClipRect);

	XL_BITMAP_HANDLE hClipBitmap = XL_ClipSubBindBitmap(hBitmapDest, lpDestClipRect);
	assert(hClipBitmap);

    XLUE_RESOURCE_HANDLE hRes = NULL;
    hRes = m_SvgRes.GetHandle();
    wxSVGDocument* pSvgDoc = (wxSVGDocument*)XLUE_GetResRealHandle(hRes);
    assert(pSvgDoc);

    wxSVGRect srcRect;
    srcRect.SetX(lpSrcClipRect->left);
    srcRect.SetY(lpSrcClipRect->top);
    srcRect.SetWidth(lpSrcClipRect->right - lpSrcClipRect->left);
    srcRect.SetHeight(lpSrcClipRect->bottom - lpSrcClipRect->top);

    wxImage image = pSvgDoc->Render(lpDestClipRect->right-lpDestClipRect->left
        , lpDestClipRect->bottom-lpDestClipRect->top
        , &srcRect, m_preserveAspectRatio, m_enableSvgAlpha);

    XL_BITMAP_HANDLE hRendedBitmap = image.GetXLBitmapHandle();

    XLBlendHint hint;
    hint.BaseHint = *lpHint;
    hint.ConstAlpha = alpha;
    hint.BlendType = XLGRAPHIC_BLEND_SRC_ALPHA;

    XL_Blend(hClipBitmap, lpDestClipRect->left, lpDestClipRect->top, hRendedBitmap, &hint);

	XL_ReleaseBitmap(hClipBitmap);
}