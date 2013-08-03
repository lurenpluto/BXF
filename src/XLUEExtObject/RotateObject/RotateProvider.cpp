/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./RotateProvider.h"

bool DefaultRotateProvider::Rotate( XL_BITMAP_HANDLE hBitmap, SIZE bmpSize, POINT ptCenter, double angel , RotateMode mode, unsigned char alpha, XLGraphicHint* lpHint )
{
	XL_TRANSFORM_HANDLE hTransform = XL_CreateTransferTrans(-ptCenter.x, -ptCenter.y, 0);
	assert(hTransform);

	XL_TRANSFORM_HANDLE hRotate = XL_CreateRotateTrans(0, 0, angel);
	assert(hRotate);

	XL_AddSubTrans(hTransform, hRotate);

	XL_BITMAP_HANDLE hResult = XL_CreateBitmap(XLGRAPHIC_CT_ARGB32, bmpSize.cx * 2, bmpSize.cy * 2);
	assert(hResult);

	DWORD flag = 0;
	if (mode == RotateMode_antialias)
	{
		flag = XLTRANS_MODE_ANTIALIAS;
	}
	else
	{
		flag = XLTRANS_MODE_NORMAL;
	}

	XL_DoTrans(hBitmap, hResult, hTransform, flag);

	RECT rcSrc = { 0 };
	rcSrc.right = bmpSize.cx - 1;
	rcSrc.bottom = bmpSize.cy - 1;

	RECT rcDest = { 0 };
	XL_TransKeepCentreRect(hTransform, &rcSrc, &rcDest, &ptCenter);

	XL_ReleaseTrans(hRotate);
	XL_ReleaseTrans(hTransform);

	XL_FillBitmap(hBitmap, 0);

	RECT rcClip;
	if (RectHelper::IntersectRect(&rcClip, &rcSrc, &rcDest))
	{
		rcSrc = rcClip;
		::OffsetRect(&rcClip, -rcDest.left, -rcDest.top);
		XL_BITMAP_HANDLE hClipBitmap = XL_ClipSubBindBitmap(hResult, &rcClip);
		assert(hClipBitmap);

		assert(lpHint);
		XLBlendHint hint;
		hint.BaseHint = *lpHint;
		hint.ConstAlpha = alpha;
		hint.BlendType = XLGRAPHIC_BLEND_SRC_ALPHA;
		XL_Blend(hBitmap, rcSrc.left, rcSrc.top, hClipBitmap, &hint);

		XL_ReleaseBitmap(hClipBitmap);
	}

	XL_ReleaseBitmap(hResult);

	return true;
}