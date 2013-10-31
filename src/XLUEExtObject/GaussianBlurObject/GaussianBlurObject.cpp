/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"

#include "./GaussianBlurObject.h"
#include "./GaussianBlurDelegate.h"

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

void GaussianBlurObject::SetSigma(const float &sigma)
{
	if (m_sigma == sigma)
	{
		return;
	}
	m_sigma = sigma;
	if (m_type == Default)
	{
		m_radius = m_sigma * 3;
	}
	PushDirtyRect(NULL);
}

float GaussianBlurObject::GetSigma() const
{
	return m_sigma;
}

void GaussianBlurObject::SetRadius(const int &radius)
{
	m_radius = radius;
}

int GaussianBlurObject::GetRadius() const
{
	return m_radius;
}

void GaussianBlurObject::SetGaussianType(const char *type)
{
	Type iType;
	if (strcmp(type, "IIR") == 0)
	{
		iType = DirecheIIRSSE;
	} 
	else if (strcmp(type, "FIR") == 0)
	{
		iType = OneDimentionMMX;
	}
	else if (strcmp(type, "Default") == 0)
	{
		iType = Default;
	}
	else
	{
		iType = UnDefined;
	}
	if (iType != m_type && iType != UnDefined)
	{
		m_type = iType;
		PushDirtyRect(NULL);
	}
}

const char *GaussianBlurObject::GetGaussianType()const
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
	else 
	{
		return "UnDefined";
	}
}

void GaussianBlurObject::OnPaint( XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char /*alpha*/ )
{
	if (m_radius > 0 && m_sigma >0 && m_type > UnDefined && m_type < ValidType)
	{
		assert(lpSrcClipRect);
		const RECT* pos = GetPos();

		XL_BITMAP_HANDLE hClipBitmap = XL_ClipSubBindBitmap(hBitmapDest, lpDestClipRect);
		assert(hClipBitmap);
		// FIR ÐÍÂË²¨
		if (m_type == OneDimentionMMX)
		{
			OneDimentionRenderMMX(hClipBitmap, m_sigma, m_radius);
		}
		// IIR ÐÍÂË²¨
		else if (m_type == DirecheIIRSSE)
		{
			DericheIIRRenderSSE(hClipBitmap, m_sigma);
		}
		// »ìÓÃ
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
		XL_ReleaseBitmap(hClipBitmap);
	}
}
