/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./BoltBrowserObject.h"
#include "../WebKernel/WebKernelClient.h"

BoltBrowserObject::BoltBrowserObject(XLUE_LAYOUTOBJ_HANDLE hObj)
:ExtRealObjMethodsImpl(hObj)
{
	m_lpEvents = new BoltBrowserObjectEvents(m_hObj);
	m_lpBrowser = new WindowBoltBrowser(hObj, this);

	BaseBoltBrowserObject::Init(hObj, m_lpBrowser, m_lpEvents);
}

BoltBrowserObject::~BoltBrowserObject(void)
{
	BaseBoltBrowserObject::Uninit();

	assert(m_lpEvents);
	m_lpEvents->Release();
	m_lpEvents = NULL;

	assert(m_lpBrowser);
	m_lpBrowser->Release();
	m_lpBrowser = NULL;
}

void BoltBrowserObject::OnInitControl()
{

}

void BoltBrowserObject::OnDestroy()
{

}

void BoltBrowserObject::OnCreateRealWindow( BOOL bCreate, OS_HOSTWND_HANDLE hWnd )
{
	if (bCreate)
	{
		assert(m_lpBrowser);
		m_lpBrowser->Create((HWND)hWnd);
	}
	else
	{
		assert(m_lpBrowser);
		m_lpBrowser->Close(true);
	}
}

void BoltBrowserObject::OnSetRealFocus( BOOL /*focus*/ )
{

}

OS_HOSTWND_HANDLE BoltBrowserObject::OnGetRenderWindow()
{
	return NULL;
}

BoltBrowserObjectEvents* BoltBrowserObject::GetEvents( )
{
	assert(m_lpEvents);

	return m_lpEvents;
}

