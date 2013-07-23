/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./InputHandler.h"
#include <WindowsX.h>

InputHandler::InputHandler(CefBrowser* lpBrowser)
:m_browser(lpBrowser),
m_clickX(0),
m_clickY(0),
m_clickCount(0),
m_clickTime(0),
m_clickMouseType(MouseButtonType_unknown),
m_doubleClickRange(::GetSystemMetrics(SM_CXDOUBLECLK) / 2),
m_doubleClickInterval(::GetDoubleClickTime())
{
	assert(m_browser);
}

InputHandler::~InputHandler(void)
{
	assert(m_browser);
	m_browser = NULL;
}

long InputHandler::InputFilter( unsigned long actionType, unsigned long wParam, unsigned long lParam, bool& handled )
{
	assert(m_browser);

	long ret = 0;
	handled = false;

	if (actionType >= XLUE_ACTION_MOUSEFIRST
		&& actionType <= XLUE_ACTION_MOUSELAST)
	{
		ret = MouseInputFilter(actionType, wParam, lParam, handled);
	}
	else if (actionType >= XLUE_ACTION_KEYFIRST
		&& actionType <= XLUE_ACTION_KEYLAST)
	{
		ret = KeyboardInputFilter(actionType, wParam, lParam, handled);
	}

	return ret;
}

int InputHandler::GetCefMouseModifiers( WPARAM wparam ) const
{
	int modifiers = 0;

	if (wparam & XLUE_MK_LBUTTON)
	{
		modifiers |= EVENTFLAG_LEFT_MOUSE_BUTTON;
	}
	if (wparam & XLUE_MK_MBUTTON)
	{
		modifiers |= EVENTFLAG_MIDDLE_MOUSE_BUTTON;
	}
	if (wparam & XLUE_MK_RBUTTON)
	{
		modifiers |= EVENTFLAG_RIGHT_MOUSE_BUTTON;
	}

	if (wparam & XLUE_MK_CONTROL)
	{
		modifiers |= EVENTFLAG_CONTROL_DOWN;
	}
	if (wparam & XLUE_MK_SHIFT)
	{
		modifiers |= EVENTFLAG_SHIFT_DOWN;
	}

	if (IsKeyDown(VK_MENU))
	{
		modifiers |= EVENTFLAG_ALT_DOWN;
	}

	if (IsKeyToggled(VK_NUMLOCK))
	{
		modifiers |= EVENTFLAG_NUM_LOCK_ON;
	}
	if (IsKeyToggled(VK_CAPITAL))
	{
		modifiers |= EVENTFLAG_CAPS_LOCK_ON;
	}

	return modifiers;
}

int InputHandler::GetCefKeyboardModifiers( WPARAM wparam, LPARAM lparam ) const
{
	int modifiers = 0;
	if (IsKeyDown(VK_SHIFT))
	{
		modifiers |= EVENTFLAG_SHIFT_DOWN;
	}

	if (IsKeyDown(VK_CONTROL))
	{
		modifiers |= EVENTFLAG_CONTROL_DOWN;
	}

	if (IsKeyDown(VK_MENU))
	{
		modifiers |= EVENTFLAG_ALT_DOWN;
	}

	if (IsKeyToggled(VK_NUMLOCK))
	{
		modifiers |= EVENTFLAG_NUM_LOCK_ON;
	}
	if (IsKeyToggled(VK_CAPITAL))
	{
		modifiers |= EVENTFLAG_CAPS_LOCK_ON;
	}

	switch (wparam) 
	{
	case VK_RETURN:
		if ((lparam >> 16) & KF_EXTENDED)
		{
			modifiers |= EVENTFLAG_IS_KEY_PAD;
		}
		break;
	case VK_INSERT:
	case VK_DELETE:
	case VK_HOME:
	case VK_END:
	case VK_PRIOR:
	case VK_NEXT:
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
		if (!((lparam >> 16) & KF_EXTENDED))
		{
			modifiers |= EVENTFLAG_IS_KEY_PAD;
		}
		break;
	case VK_NUMLOCK:
	case VK_NUMPAD0:
	case VK_NUMPAD1:
	case VK_NUMPAD2:
	case VK_NUMPAD3:
	case VK_NUMPAD4:
	case VK_NUMPAD5:
	case VK_NUMPAD6:
	case VK_NUMPAD7:
	case VK_NUMPAD8:
	case VK_NUMPAD9:
	case VK_DIVIDE:
	case VK_MULTIPLY:
	case VK_SUBTRACT:
	case VK_ADD:
	case VK_DECIMAL:
	case VK_CLEAR:
		modifiers |= EVENTFLAG_IS_KEY_PAD;
		break;
	case VK_SHIFT:
		if (IsKeyDown(VK_LSHIFT))
		{
			modifiers |= EVENTFLAG_IS_LEFT;
		}
		else if (IsKeyDown(VK_RSHIFT))
		{
			modifiers |= EVENTFLAG_IS_RIGHT;
		}
		break;
	case VK_CONTROL:
		if (IsKeyDown(VK_LCONTROL))
		{
			modifiers |= EVENTFLAG_IS_LEFT;
		}
		else if (IsKeyDown(VK_RCONTROL))
		{
			modifiers |= EVENTFLAG_IS_RIGHT;
		}
		break;
	case VK_MENU:
		if (IsKeyDown(VK_LMENU))
		{
			modifiers |= EVENTFLAG_IS_LEFT;
		}
		else if (IsKeyDown(VK_RMENU))
		{
			modifiers |= EVENTFLAG_IS_RIGHT;
		}
		break;
	case VK_LWIN:
		modifiers |= EVENTFLAG_IS_LEFT;
		break;
	case VK_RWIN:
		modifiers |= EVENTFLAG_IS_RIGHT;
		break;

	default:
		break;
	}

	return modifiers;
}

bool InputHandler::IsKeyDown( int vk ) const
{
	return !!(::GetKeyState(vk) & 0x1000);
}

bool InputHandler::IsKeyToggled( int vk ) const
{
	return !!(::GetKeyState(vk) & 0x0001);
}

void InputHandler::UpdateClick( unsigned long actionType, unsigned long wParam, unsigned long lParam )
{
	MouseButtonType curType = MouseButtonType_unknown;

	bool needCancel = false;
	bool needHandle = true;

	if (actionType == XLUE_ACTION_MOUSE_MOVE
		|| actionType == XLUE_ACTION_MOUSE_LEAVE)
	{
		needCancel = true;
	}
	else if (actionType == XLUE_ACTION_LMOUSE_DOWN
		|| actionType == XLUE_ACTION_LMOUSE_DBCLICK)
	{
		curType = MouseButtonType_left;
	}
	else if (actionType == XLUE_ACTION_RMOUSE_DOWN
		|| actionType == XLUE_ACTION_RMOUSE_DBCLICK)
	{
		curType = MouseButtonType_right;
	}
	else if (actionType == XLUE_ACTION_MMOUSE_DOWN
		|| actionType == XLUE_ACTION_MMOUSE_DBCLICK)
	{
		curType = MouseButtonType_mid;
	}
	else
	{
		needHandle = false;
	}
	
	if (!needHandle)
	{
		return;
	}
	else if (needCancel)
	{
		m_clickMouseType = MouseButtonType_unknown;
		m_clickTime = 0;
		m_clickX = 0;
		m_clickY = 0;
		m_clickCount = 0;

		return;
	}

	assert(curType != MouseButtonType_unknown);

	int x = GET_X_LPARAM(lParam);
	int y = GET_Y_LPARAM(lParam);
	long curTime = ::GetMessageTime();

	bool needReset = false;
	if (m_clickMouseType == curType)
	{
		if ((abs(m_clickX - x) > m_doubleClickRange)
			|| (abs(m_clickY - y) > m_doubleClickRange)
			|| ((curTime - m_clickTime) > (long)m_doubleClickInterval))
		{
			needReset = true;
		}
	}
	else
	{
		needReset = true;
	}

	m_clickX = x;
	m_clickY = y;
	m_clickTime = curTime;

	if (needReset)
	{
		m_clickMouseType = curType;
		m_clickCount = 1;
	}
	else
	{
		++m_clickCount;
	}
}

long InputHandler::MouseInputFilter( unsigned long actionType, unsigned long wParam, unsigned long lParam, bool& handled )
{
	handled = true;

	UpdateClick(actionType, wParam, lParam);

	assert(m_browser);
	CefRefPtr<CefBrowserHost> spHost = m_browser->GetHost();
	assert(spHost);

	CefMouseEvent mouseEvent;
	mouseEvent.x = GET_X_LPARAM(lParam);
	mouseEvent.y = GET_Y_LPARAM(lParam);
	mouseEvent.modifiers = GetCefMouseModifiers(wParam);

	if (actionType == XLUE_ACTION_MOUSE_MOVE)
	{
		spHost->SendMouseMoveEvent(mouseEvent, false);
	}
	else if (actionType == XLUE_ACTION_MOUSE_WHEEL)
	{
		int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		bool isShift = IsKeyDown(VK_SHIFT);

		spHost->SendMouseWheelEvent(mouseEvent, isShift ? delta : 0, isShift ? 0 : delta);
	}
	else if (actionType == XLUE_ACTION_MOUSE_LEAVE)
	{
		mouseEvent.x = mouseEvent.y = 0;
		spHost->SendMouseMoveEvent(mouseEvent, true);
	}
	else 
	{
		bool ignore = false;
		bool mouseUp = false;
		CefBrowserHost::MouseButtonType btnType;

		if (actionType == XLUE_ACTION_LMOUSE_DOWN || actionType == XLUE_ACTION_LMOUSE_DBCLICK)
		{
			btnType = MBT_LEFT;
			mouseUp = false;
		}
		else if (actionType == XLUE_ACTION_LMOUSE_UP)
		{
			btnType = MBT_LEFT;
			mouseUp = true;
		}
		else if (actionType == XLUE_ACTION_RMOUSE_DOWN || actionType == XLUE_ACTION_RMOUSE_DBCLICK)
		{
			btnType = MBT_RIGHT;
			mouseUp = false;
		}
		else if (actionType == XLUE_ACTION_RMOUSE_UP)
		{
			btnType = MBT_RIGHT;
			mouseUp = true;
		}
		else if (actionType == XLUE_ACTION_MMOUSE_DOWN || actionType == XLUE_ACTION_MMOUSE_DBCLICK)
		{
			btnType = MBT_MIDDLE;
			mouseUp = false;
		}
		else if (actionType == XLUE_ACTION_MMOUSE_UP)
		{
			btnType = MBT_MIDDLE;
			mouseUp = true;
		}
		else
		{
			// mouseenter和第一个mousemove相同，忽略
			// mousehover 浏览器消息不需要
			ignore = true;
			handled = false;
		}

		if (!ignore)
		{
			spHost->SendMouseClickEvent(mouseEvent, btnType, mouseUp, m_clickCount);
		}
	}

	return 0;
}

long InputHandler::KeyboardInputFilter( unsigned long actionType, unsigned long wParam, unsigned long lParam, bool& handled )
{
	handled = true;

	CefKeyEvent keyEvent;

	if (actionType == XLUE_ACTION_KEY_DOWN || actionType == XLUE_ACTION_SYSKEY_DOWN)
	{
		keyEvent.type = KEYEVENT_RAWKEYDOWN;
	}
	else if (actionType == XLUE_ACTION_KEY_UP || actionType == XLUE_ACTION_SYSKEY_UP)
	{
		keyEvent.type = KEYEVENT_KEYUP;
	}
	else if (actionType == XLUE_ACTION_CHAR || actionType == XLUE_ACTION_SYSCHAR)
	{
		keyEvent.type = KEYEVENT_CHAR;
	}
	else
	{
		handled = false;
		return 0;
	}

	keyEvent.windows_key_code = wParam;
	keyEvent.native_key_code = lParam;
	keyEvent.is_system_key = false;
	keyEvent.modifiers = GetCefKeyboardModifiers(wParam, lParam);

	if (actionType == XLUE_ACTION_SYSKEY_UP
		|| actionType == XLUE_ACTION_SYSKEY_DOWN
		|| actionType == XLUE_ACTION_SYSCHAR)
	{
		keyEvent.is_system_key = true;
	}


	assert(m_browser);
	CefRefPtr<CefBrowserHost> spHost = m_browser->GetHost();
	assert(spHost);

	spHost->SendKeyEvent(keyEvent);

	return 0;
}