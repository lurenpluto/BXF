/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./GaussianBlurObject.h"
#include "GaussianBlurDelegate.h"

#include <iostream>
#include <time.h>

GaussianBlurObject::GaussianBlurObject( XLUE_LAYOUTOBJ_HANDLE hObj )
:ExtLayoutObjMethodsImpl(hObj)
, m_sigma(1)
, m_radius(3)
, m_type(Default)
{
}

GaussianBlurObject::~GaussianBlurObject(void)
{
}

void GaussianBlurObject::SetSigma(double sigma)
{
	if (m_sigma == sigma)
	{
		return;
	}
	m_sigma = sigma;
	PushDirtyRect(NULL);
}

void GaussianBlurObject::SetType(const char *type)
{
	Type iType = UnDefined;
	if (strcmp(type, "IIR"))
	{
		iType = DirecheIIRSSE;
	} 
	else if (strcmp(type, "FIR"))
	{
		iType = OneDimentionMMX;
	}
	else if (strcmp(type, "Default"))
	{
		iType = Default;
	}
	if (iType != m_type && iType != UnDefined)
	{
		m_type = iType;
		PushDirtyRect(NULL);
	}
}

const char *GaussianBlurObject::GetType()const
{
	if (m_type == DirecheIIRSSE)
	{
		return "IIR";
	}
	else if (m_type == OneDimentionMMX)
	{
		return "FIR";
	}
	else if (m_type == Default)
	{
		return "Default";
	}
}

void GaussianBlurObject::OnPaint( XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char /*alpha*/ )
{
	clock_t time1 = clock();

	assert(lpSrcClipRect);
	const RECT* pos = GetPos();

	XL_BITMAP_HANDLE hClipBitmap = XL_ClipSubBindBitmap(hBitmapDest, lpDestClipRect);
	assert(hClipBitmap);

	if (m_radius > 0 && m_sigma >0)
	{
		// FIR ÐÍÂË²¨
		if (m_type == OneDimentionMMX)
		{
			for (int i = 0; i < 1; i++)
			OneDimentionRenderMMX(hClipBitmap, m_sigma, m_radius);
		}
		// IIR ÐÍÂË²¨
		else if (m_type == DirecheIIRSSE)
		{
			for (int i = 0; i < 1; i++)
			DericheIIRRenderSSE(hClipBitmap, m_sigma);
		}
		else if (m_type == Default)
		{
			if (m_radius <= 3)
			{
				OneDimentionRenderMMX(hClipBitmap, m_sigma, m_radius);
			}
			else
			{
				DericheIIRRenderSSE(hClipBitmap, m_sigma);
			}
		}
	}

	XL_ReleaseBitmap(hClipBitmap);
	clock_t time2=clock();
	float diff = (((float)time2 - (float)time1) / 1000000.0F ) * 1000; 
}
