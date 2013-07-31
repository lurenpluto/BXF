/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./HostWndIconObject.h"
#include <atlbase.h>
#include <atlwin.h>

HostWndIconObject::HostWndIconObject(XLUE_LAYOUTOBJ_HANDLE hObj)
:ExtLayoutObjMethodsImpl(hObj),
m_inApplying(false)
{
	m_bigIcon.SetOwner(this);
	m_bigIcon.SetResFunc(&HostWndIconObject::OnBigIconResChange, NULL);
	m_smallIcon.SetResFunc(&HostWndIconObject::OnSmallIconResChange, NULL);

	m_bigIcon.SetResProvider(GetResProvider());
	m_smallIcon.SetResProvider(GetResProvider());
}

HostWndIconObject::~HostWndIconObject(void)
{
}

void HostWndIconObject::OnCreateHostWnd( XLUE_OBJTREE_HANDLE /*hTree*/, XLUE_HOSTWND_HANDLE hHostWnd, BOOL bCreate )
{
	assert(hHostWnd);
	HWND wnd = (HWND)XLUE_GetHostWndWindowHandle(hHostWnd);
	assert(::IsWindow(wnd));

	if (bCreate)
	{
		ApplyIcon(wnd, true);
		ApplyIcon(wnd, false);
	}
}

void HostWndIconObject::SetIconResID( const char* resID, bool big )
{
	if (big)
	{
		m_bigIcon.SetResID(resID);
	}
	else
	{
		m_smallIcon.SetResID(resID);
	}
}

const char* HostWndIconObject::GetIconResID( bool big )
{
	if (big)
	{
		return m_bigIcon.GetID();
	}
	else
	{
		return m_smallIcon.GetID();
	}
}


void HostWndIconObject::ApplyIcon( HWND hWnd, bool big )
{
	if (m_inApplying)
	{
		return;
	}

	ApplyIconImpl(hWnd, big);

	m_inApplying = false;
}

void HostWndIconObject::OnBigIconResChange()
{
	HostWndWrapper hostwnd = GetBindHostWnd();
	if (hostwnd.IsValid())
	{
		HWND hWnd = (HWND)hostwnd.GetWindowHandle();
		if (hWnd != NULL)
		{
			ApplyIcon(hWnd, true);
		}
	}
}

void HostWndIconObject::OnSmallIconResChange()
{
	HostWndWrapper hostwnd = GetBindHostWnd();
	if (hostwnd.IsValid())
	{
		HWND hWnd = (HWND)hostwnd.GetWindowHandle();
		if (hWnd != NULL)
		{
			ApplyIcon(hWnd, false);
		}
	}
}

void HostWndIconObject::ApplyIconImpl( HWND hWnd, bool big )
{
	XLUE_RESOURCE_HANDLE hRes = NULL;

	if (big)
	{
		hRes = m_bigIcon.GetHandle();
	}
	else
	{
		hRes = m_smallIcon.GetHandle();
	}

	assert(hRes);
	if (hRes == NULL)
	{
		return;
	}

	XLGP_ICON_HANDLE hIcon = (XLGP_ICON_HANDLE)XLUE_GetResRealHandle(hRes);
	assert(hIcon);
	if (hIcon == NULL)
	{
		return;
	}

	HICON hSysIcon = XLGP_IconGetHandle(hIcon);
	if (hSysIcon != NULL)
	{
		CWindow(hWnd).SetIcon(hSysIcon, big? TRUE : FALSE);
	}

	XLUE_ReleaseResRealHandle(hRes, hIcon);
}

void HostWndIconObject::SetIcon( XLUE_RESOURCE_HANDLE hResHandle, bool big )
{
	if (big)
	{
		m_bigIcon.SetHandle(hResHandle);
	}
	else
	{
		m_smallIcon.SetHandle(hResHandle);
	}
}

XLUE_RESOURCE_HANDLE HostWndIconObject::GetIcon( bool big )
{
	XLUE_RESOURCE_HANDLE hResHandle = NULL;

	if (big)
	{
		hResHandle = m_bigIcon.GetHandle();
	}
	else
	{
		hResHandle = m_smallIcon.GetHandle();
	}

	return hResHandle;
}