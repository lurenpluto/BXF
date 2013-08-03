/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./RotateObject.h"

RotateObject::RotateObject( XLUE_LAYOUTOBJ_HANDLE hObj )
:ExtLayoutObjMethodsImpl(hObj)
{
	m_lpRotateProvider = new DefaultRotateProvider();
}

RotateObject::~RotateObject(void)
{
	assert(m_lpRotateProvider);
	delete m_lpRotateProvider;
	m_lpRotateProvider = NULL;
}

void RotateObject::OnBind()
{
	m_objPos = *GetPos();

	m_centerPtExp.BindRect(&m_objPos);

	m_centerPtExp.Cacl();
	m_centerPtExp.GetValue(m_centerPt);
}

void RotateObject::OnPosChanged( const RECT* lpOldPos, const RECT* lpNewPos )
{
	assert(lpOldPos);
	assert(lpNewPos);

	m_objPos = *lpNewPos;

	OnExpChange();
}

void RotateObject::OnPaintEx( XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect
						   , const RECT* lpSrcClipRect, unsigned char alpha, XLGraphicHint* lpHint )
{
	assert(m_lpRotateProvider);

	assert(lpSrcClipRect);
	assert(RectHelper::EqualRect(lpSrcClipRect, GetPos()));

	if (m_angel == 0)
	{
		return;
	}

	XL_BITMAP_HANDLE hClipBitmap = XL_ClipSubBindBitmap(hBitmapDest, lpDestClipRect);
	assert(hClipBitmap);

	SIZE bmpSize = {lpDestClipRect->right - lpDestClipRect->left, lpDestClipRect->bottom - lpDestClipRect->top};

	assert(m_lpRotateProvider);
	m_lpRotateProvider->Rotate(hClipBitmap, bmpSize, m_centerPt, m_angel, GetRotateMode(), alpha, lpHint);

	XL_ReleaseBitmap(hClipBitmap);
}

void RotateObject::SetAngel( double angel )
{
	if (angel == m_angel)
	{
		return;
	}

	m_angel = angel;

	PushDirtyRect(NULL);
}

double RotateObject::GetAngel() const
{
	return m_angel;
}

bool RotateObject::SetStringX( const char* value )
{
	if (!m_centerPtExp.SetStringX(value))
	{
		assert(false);
		return false;
	}

	OnExpChange();
	
	return true;
}

bool RotateObject::SetNumberX( int value )
{
	if (!m_centerPtExp.SetNumberX(value))
	{
		assert(false);
		return false;
	}

	OnExpChange();

	return true;
}

bool RotateObject::SetStringY( const char* value )
{
	if (!m_centerPtExp.SetStringY(value))
	{
		assert(false);
		return false;
	}

	OnExpChange();

	return true;
}

bool RotateObject::SetNumberY( int value )
{
	if (!m_centerPtExp.SetNumberY(value))
	{
		assert(false);
		return false;
	}
	
	OnExpChange();

	return true;
}

void RotateObject::OnExpChange()
{
	if (m_centerPtExp.IsBind() && m_centerPtExp.Cacl())
	{
		m_centerPtExp.GetValue(m_centerPt);
		PushDirtyRect(NULL);
	}
}

void RotateObject::SetRotateMode( RotateMode mode )
{
	if (m_mode == mode)
	{
		return;
	}

	m_mode = mode;

	PushDirtyRect(NULL);
}

RotateMode RotateObject::GetRotateMode() const
{
	return m_mode;
}

POINT RotateObject::GetCenter() const
{
	return m_centerPt;
}