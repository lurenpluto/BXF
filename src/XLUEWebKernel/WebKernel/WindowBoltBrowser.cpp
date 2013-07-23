/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WindowBoltBrowser.h"

WindowBoltBrowser::WindowBoltBrowser( XLUE_LAYOUTOBJ_HANDLE hObj, BoltBrowserEvents* lpEvents )
:BaseBoltBrowser(hObj, lpEvents)
{

}

WindowBoltBrowser::~WindowBoltBrowser()
{

}

bool WindowBoltBrowser::Create( HWND hParent )
{
	assert(hParent);
	assert(::IsWindow(hParent));
	assert(m_obj);

	CefWindowInfo info;

	const RECT* lpPos = m_obj.GetAbsPos();
	assert(lpPos);

	RECT rcWeb;
	rcWeb.left = rcWeb.top = 0;
	rcWeb.right = lpPos->right - lpPos->left + 100;
	rcWeb.bottom = lpPos->bottom - lpPos->top + 100;

	info.SetAsChild(hParent, rcWeb);

	return BaseBoltBrowser::Create(info);
}

void WindowBoltBrowser::OnAfterCreated()
{
	assert(m_browser);

	m_obj.SetRealWindow(m_browser->GetHost()->GetWindowHandle());

	BaseBoltBrowser::OnAfterCreated();
}

void WindowBoltBrowser::OnBeforeClose()
{
	BaseBoltBrowser::OnBeforeClose();
}

bool WindowBoltBrowser::Close( bool force )
{
	m_obj.SetRealWindow(NULL);

	return BaseBoltBrowser::Close(force);
}

void WindowBoltBrowser::SetRealFocus()
{

}

