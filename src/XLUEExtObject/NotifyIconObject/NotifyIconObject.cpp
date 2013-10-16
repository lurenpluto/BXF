/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./NotifyIconObject.h"
#include "./NotifyIconObjectEvents.h"

#include <ShellAPI.h>

unsigned int NotifyIconWindow::s_taskbarCreateMsg = ::RegisterWindowMessage(L"TaskbarCreated");

NotifyIconWindow::NotifyIconWindow()
:m_lpOwner(NULL)
{
}

NotifyIconWindow::~NotifyIconWindow()
{
	assert(m_lpOwner);
	m_lpOwner = NULL;
}

LRESULT NotifyIconWindow::OnNotify( UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/ )
{
	assert(m_lpOwner);
	m_lpOwner->OnNotify(wParam, lParam);

	return 0;
}

LRESULT NotifyIconWindow::OnTaskbarCreate( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	assert(m_lpOwner);
	m_lpOwner->OnTaskbarCreate();

	return 0;
}

void NotifyIconWindow::SetOwner( NotifyIconObject* lpOwner )
{
	assert(lpOwner);
	m_lpOwner = lpOwner;
}

NotifyIconObject::NotifyIconObject( XLUE_LAYOUTOBJ_HANDLE hObj )
:ExtLayoutObjMethodsImpl(hObj)
,m_status(NotifyIconStatus_removed)
,m_iconVisible(true)
{
	m_lpEvents = new NotifyIconObjectEvents(GetObjectHandle());

	m_lpNotifyWindow = new SafeWindowWrapper<NotifyIconWindow>();
	m_lpNotifyWindow->SetOwner(this);

	m_icon.SetOwner(this);
	m_icon.SetResProvider(GetResProvider());
	m_icon.SetResFunc(&NotifyIconObject::OnIconResChange, NULL);
}

NotifyIconObject::~NotifyIconObject( void )
{
	assert(m_lpNotifyWindow);
	m_lpNotifyWindow->SafeDelete();
	m_lpNotifyWindow = NULL;
}

void NotifyIconObject::SetIconResID( const char* resID )
{
	m_icon.SetResID(resID);
}

const char* NotifyIconObject::GetIconResID() const
{
	return m_icon.GetID();
}

void NotifyIconObject::SetIcon( XLUE_RESOURCE_HANDLE hResHandle )
{
	m_icon.SetHandle(hResHandle);
}

XLUE_RESOURCE_HANDLE NotifyIconObject::GetIcon()
{
	return m_icon.GetHandle();
}

void NotifyIconObject::OnNotify( WPARAM /*wParam*/, LPARAM lParam )
{
	ProcessNormalInput((unsigned int)lParam);

	AutoSafeLock lock(this);

	bool handled = false;
	switch(lParam)
	{
	case WM_CONTEXTMENU:
		{
			POINT pt;
			::GetCursorPos(&pt);

			m_lpEvents->OnContextMenu(pt.x, pt.y, GetKeyFlags(), handled);
		}
		break;
	case NIN_KEYSELECT:
		m_lpEvents->OnKeySelect(handled);
		break;

	case NIN_SELECT:
		m_lpEvents->OnSelect(handled);
		break;

	case NIN_BALLOONSHOW:
		m_lpEvents->OnBalloonShow(handled);
		break;
	case NIN_BALLOONHIDE:
		m_lpEvents->OnBalloonHide(handled);
		break;
	case NIN_BALLOONTIMEOUT:
		m_lpEvents->OnBalloonTimeout(handled);
		break;
	case NIN_BALLOONUSERCLICK:
		m_lpEvents->OnBalloonUserClick(handled);
		break;
	default:
		// dp nothing
		break;
	}
}

void NotifyIconObject::OnTaskbarCreate()
{
	if (GetVisible() && m_lpNotifyWindow->IsWindow())
	{
		AddIcon();
		UpdateVisible();
	}
}

bool NotifyIconObject::AddIcon()
{
	assert(m_lpNotifyWindow);
	assert(m_lpNotifyWindow->IsWindow());
	assert(m_status == NotifyIconStatus_removed);

	NOTIFYICONDATA notifyData = { sizeof(notifyData) };

	notifyData.uFlags = NIF_ICON | NIF_MESSAGE;
	notifyData.hIcon = GetIconHandle();
	notifyData.hWnd = m_lpNotifyWindow->m_hWnd;
	notifyData.uCallbackMessage = NotifyIconWindow::UWM_NOTIFYICON_NOTIFY;

	BOOL ret = ::Shell_NotifyIcon(NIM_ADD, &notifyData);
	assert(ret);

	notifyData.uVersion = 4; // NOTIFYICON_VERSION_4
	ret = ::Shell_NotifyIcon(NIM_SETVERSION, &notifyData);
	assert(ret);

	m_status = NotifyIconStatus_added;

	return !!ret;
}

HICON NotifyIconObject::GetIconHandle()
{
	XLUE_RESOURCE_HANDLE hRes = m_icon.GetHandle();
	//assert(hRes);
	if (hRes == NULL)
	{
		return NULL;
	}

	XLGP_ICON_HANDLE hIcon = (XLGP_ICON_HANDLE)XLUE_GetResRealHandle(hRes);
	assert(hIcon);
	if (hIcon == NULL)
	{
		return NULL;
	}

	HICON hSysIcon = XLGP_IconGetHandle(hIcon);
	assert(hSysIcon);

	XLUE_ReleaseResRealHandle(hRes, hIcon);

	return hSysIcon;
}

bool NotifyIconObject::RemoveIcon()
{
	assert(m_lpNotifyWindow);
	assert(m_lpNotifyWindow->IsWindow());
	assert(m_status == NotifyIconStatus_added);

	NOTIFYICONDATA notifyData = { sizeof(notifyData) };

	notifyData.hWnd = m_lpNotifyWindow->m_hWnd;

	BOOL ret = ::Shell_NotifyIcon(NIM_DELETE, &notifyData);
	assert(ret);

	m_status = NotifyIconStatus_removed;

	return !!ret;
}

bool NotifyIconObject::UpdateTip()
{
	assert(m_lpNotifyWindow);
	assert(m_lpNotifyWindow->IsWindow());
	assert(m_status == NotifyIconStatus_added);

	NOTIFYICONDATA notifyData = { sizeof(notifyData) };

	notifyData.uFlags = NIF_TIP;
	notifyData.hWnd = m_lpNotifyWindow->m_hWnd;
	::wcsncpy(notifyData.szTip, m_message.c_str(), sizeof(notifyData.szTip) / sizeof(wchar_t));

	BOOL ret = ::Shell_NotifyIcon(NIM_MODIFY, &notifyData);
	assert(ret);

	return !!ret; 
}

void NotifyIconObject::OnInitControl()
{
	assert(m_lpNotifyWindow);
	assert(!m_lpNotifyWindow->IsWindow());

	m_lpNotifyWindow->Create(HWND_MESSAGE);
	assert(m_lpNotifyWindow->IsWindow());

	if (GetVisible())
	{
		AddIcon();
		UpdateVisible();
	}
}

void NotifyIconObject::OnDestroy()
{
	if (GetVisible())
	{
		RemoveIcon();
	}

	assert(m_lpNotifyWindow->IsWindow());
	m_lpNotifyWindow->DestroyWindow();
}

void NotifyIconObject::OnVisibleChange( BOOL bVisible )
{
	if (m_lpNotifyWindow->IsWindow())
	{
		if (bVisible)
		{
			AddIcon();
			UpdateVisible();
		}
		else
		{
			RemoveIcon();
		}
	}
}

bool NotifyIconObject::CanHandleInput()
{
	return false;
}

bool NotifyIconObject::SetIconVisible(bool visible)
{
	if (m_iconVisible == visible)
	{
		return true;
	}

	m_iconVisible = visible;

	if (m_status == NotifyIconStatus_added)
	{
		UpdateVisible();
	}

	return true;
}

bool NotifyIconObject::UpdateInfo( const wchar_t* lpInfo, const wchar_t* lpTitle, unsigned int timeout, unsigned int flags )
{
	assert(lpInfo);

	assert(m_lpNotifyWindow);
	assert(m_lpNotifyWindow->IsWindow());

	NOTIFYICONDATA notifyData = { sizeof(notifyData) };
	notifyData.uFlags = NIF_INFO;

	if (lpInfo != NULL)
	{
		::wcsncpy(notifyData.szTip, lpInfo, sizeof(notifyData.szTip) / sizeof(wchar_t));
	}

	if (lpTitle != NULL)
	{
		::wcsncpy(notifyData.szInfoTitle, lpTitle, sizeof(notifyData.szInfoTitle) / sizeof(wchar_t));
	}

	notifyData.uTimeout = timeout;
	notifyData.dwInfoFlags = flags;

	BOOL ret =  ::Shell_NotifyIcon(NIM_MODIFY, &notifyData);
	assert(ret);

	return !!ret;
}

void NotifyIconObject::SetTip( const wchar_t* lpMessage )
{
	if (lpMessage != NULL)
	{
		if (::wcscmp(m_message.c_str(), lpMessage) == 0)
		{
			return;
		}

		m_message = lpMessage;
	}
	else
	{
		if (m_message.empty())
		{
			return;
		}

		m_message.clear();
	}

	if (m_status == NotifyIconStatus_added)
	{
		UpdateTip();
	}
}

const wchar_t* NotifyIconObject::GetTip()
{
	return m_message.c_str();
}

bool NotifyIconObject::GetIconVisible()
{
	return m_iconVisible;
}

bool NotifyIconObject::UpdateVisible()
{
	assert(m_lpNotifyWindow);
	assert(m_lpNotifyWindow->IsWindow());
	assert(m_status == NotifyIconStatus_added);

	NOTIFYICONDATA notifyData = { sizeof(notifyData) };

	notifyData.uFlags = NIF_STATE;

	if (m_iconVisible)
	{
		notifyData.dwState = NIS_SHAREDICON;
	}
	else
	{
		notifyData.dwState = NIS_HIDDEN;
	}

	notifyData.dwStateMask = NIS_HIDDEN;
	notifyData.hWnd = m_lpNotifyWindow->m_hWnd;

	BOOL ret =  ::Shell_NotifyIcon(NIM_MODIFY, &notifyData);
	assert(ret);

	return !!ret;
}

void NotifyIconObject::OnIconResChange()
{
	if (m_status == NotifyIconStatus_added)
	{
		UpdateIcon();
	}
}

bool NotifyIconObject::UpdateIcon()
{
	assert(m_lpNotifyWindow);
	assert(m_lpNotifyWindow->IsWindow());
	assert(m_status == NotifyIconStatus_added);

	NOTIFYICONDATA notifyData = { sizeof(notifyData) };

	notifyData.uFlags = NIF_ICON;
	notifyData.hIcon = GetIconHandle();
	notifyData.hWnd = m_lpNotifyWindow->m_hWnd;
	notifyData.uCallbackMessage = NotifyIconWindow::UWM_NOTIFYICON_NOTIFY;

	BOOL ret = ::Shell_NotifyIcon(NIM_MODIFY, &notifyData);
	assert(ret);

	return !!ret;
}

bool NotifyIconObject::ProcessNormalInput( unsigned int msg )
{
	unsigned long actionType = 0;

	switch(msg)
	{
	case WM_MOUSEMOVE:
		actionType = XLUE_ACTION_MOUSE_MOVE;
		break;

	case WM_LBUTTONDOWN:
		actionType = XLUE_ACTION_LMOUSE_DOWN;
		break;
	case WM_LBUTTONUP:
		actionType = XLUE_ACTION_LMOUSE_UP;
		break;
	case WM_LBUTTONDBLCLK:
		actionType = XLUE_ACTION_LMOUSE_DBCLICK;
		break;

	case WM_RBUTTONDOWN:
		actionType = XLUE_ACTION_RMOUSE_DOWN;
		break;
	case WM_RBUTTONUP:
		actionType = XLUE_ACTION_RMOUSE_UP;
		break;
	case WM_RBUTTONDBLCLK:
		actionType = XLUE_ACTION_RMOUSE_DBCLICK;
		break;

	case WM_MBUTTONDOWN:
		actionType = XLUE_ACTION_MMOUSE_DOWN;
		break;
	case WM_MBUTTONUP:
		actionType = XLUE_ACTION_MMOUSE_UP;
		break;
	case WM_MBUTTONDBLCLK:
		actionType = XLUE_ACTION_MMOUSE_DBCLICK;
		break;

	default:
		actionType = 0;
		break;
	}

	if (actionType == 0)
	{
		return false;
	}

	POINT pt;
	::GetCursorPos(&pt);

	unsigned long flags = GetKeyFlags();

	BOOL handled = FALSE;
	XLUE_ObjProcessInput(GetObjectHandle(), actionType, flags, actionType, &handled);

	return true;
}

NotifyIconObjectEvents* NotifyIconObject::GetEventContainer()
{
	assert(m_lpEvents);
	return m_lpEvents;
}

unsigned long NotifyIconObject::GetKeyFlags() const
{
	unsigned long flags = 0;
	if (::GetKeyState(VK_CONTROL) & 0x1000)
	{
		flags |= MK_CONTROL;
	}
	if (::GetKeyState(VK_SHIFT) & 0x1000)
	{
		flags |= MK_SHIFT;
	}
	if (::GetKeyState(VK_LBUTTON) & 0x1000)
	{
		flags |= MK_LBUTTON;
	}
	if (::GetKeyState(VK_RBUTTON) & 0x1000)
	{
		flags |= MK_RBUTTON;
	}
	if (::GetKeyState(VK_MBUTTON) & 0x1000)
	{
		flags |= MK_MBUTTON;
	}

	return flags;
}

bool NotifyIconObject::ShowBalloonTip( const wchar_t* lpMessage, const wchar_t* lpTitle, unsigned int timeout, unsigned int iconFlags )
{
	assert(m_lpNotifyWindow);
	assert(m_lpNotifyWindow->IsWindow());
	assert(m_status == NotifyIconStatus_added);
	if (m_status != NotifyIconStatus_added)
	{
		return false;
	}

	NOTIFYICONDATA notifyData = { sizeof(notifyData) };

	notifyData.uFlags = NIF_INFO;

	if (lpMessage != NULL)
	{
		::wcsncpy(notifyData.szInfo, lpMessage, sizeof(notifyData.szInfo) / sizeof(wchar_t));
	}

	if (lpTitle != NULL)
	{
		::wcsncpy(notifyData.szInfoTitle, lpTitle, sizeof(notifyData.szInfoTitle) / sizeof(wchar_t));
	}

	notifyData.uTimeout = timeout;

	notifyData.dwInfoFlags = iconFlags;

	notifyData.hWnd = m_lpNotifyWindow->m_hWnd;

	BOOL ret =  ::Shell_NotifyIcon(NIM_MODIFY, &notifyData);
	assert(ret);

	return !!ret;
}