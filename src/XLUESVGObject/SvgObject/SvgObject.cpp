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
, m_objWidth(0)
, m_objHeight(0)
{
    m_SVGRes.SetOwner(this);
    m_SVGRes.SetResFunc(&SVGObject::OnSVGResChange, NULL);

    m_SVGRes.SetResProvider(GetResProvider());
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
    //��Դ�ı�ʱҪ���»���
    m_isDirty = true;
}

void SVGObject::OnAbsPosChanged(const RECT* lpOldAbsPos, const RECT* lpNewAbsPos)
{
    //������ı��СҪ���»���
    if (m_objWidth != lpNewAbsPos->right - lpNewAbsPos->left
        || m_objHeight != lpNewAbsPos->bottom - lpNewAbsPos->top)
    {
        m_isDirty = true;
        m_objWidth = lpNewAbsPos->right - lpNewAbsPos->left;
        m_objHeight = lpNewAbsPos->bottom - lpNewAbsPos->top;
    }
}

void SVGObject::OnPaintEx( XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char alpha, XLGraphicHint* lpHint )
{
	assert(lpSrcClipRect);
    
    //�����󳤿�Ϊ0ʱ�������κ���Ⱦ
    if (m_objWidth == 0 || m_objHeight == 0)
    {
        return;
    }

    if (m_isDirty)
    {
        XLUE_RESOURCE_HANDLE hRes = NULL;
        hRes = m_SVGRes.GetHandle();
        wxSVGDocument* pSVGDoc = (wxSVGDocument*)XLUE_GetResRealHandle(hRes);
        assert(pSVGDoc);

        if (pSVGDoc == NULL)
        {
            return;
        }

        //��Ϊ��ʸ��ͼ�Σ�ͼƬ�Ŀ�߾ͱ���Ϊ�Ƕ���Ŀ�ߣ�����������ζ����������ͼƬ
        m_imageCache = pSVGDoc->Render(m_objWidth, m_objHeight
            , NULL, m_preserveAspectRatio, m_enableSVGAlpha);
        m_isDirty = false;
    }

    XL_BITMAP_HANDLE hRendedBitmap = m_imageCache.GetXLBitmapHandle();

    //�Ӵ�ͼ����һ��������ΪԴ����
    XL_BITMAP_HANDLE hClipedSrcBitmap = XL_ClipSubBindBitmap(hRendedBitmap, lpSrcClipRect);

    XLBlendHint hint;
    hint.BaseHint = *lpHint;
    hint.ConstAlpha = alpha;
    hint.BlendType = XLGRAPHIC_BLEND_SRC_ALPHA;

    XL_Blend(hBitmapDest, lpDestClipRect->left, lpDestClipRect->top, hClipedSrcBitmap, &hint);

    XL_ReleaseBitmap(hClipedSrcBitmap);
}