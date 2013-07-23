/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   InputHandler
*   Author      :   李亚星
*   Create      :   2013-6-12 
*   LastChange  :   2013-6-12
*   History     :	
*
*   Description :   windowless模式下的键盘和鼠标消息的处理辅助类
*
********************************************************************/ 
#ifndef __INPUTHANDLER_H__
#define __INPUTHANDLER_H__

class InputHandler
{
private:

	enum MouseButtonType
	{
		MouseButtonType_unknown = 0,
		MouseButtonType_left = 1,
		MouseButtonType_mid = 2,
		MouseButtonType_right = 3,
	};

public:
	InputHandler(CefBrowser* lpBrowser);
	~InputHandler(void);

	long InputFilter(unsigned long actionType, unsigned long wParam, unsigned long lParam, bool& handled);

private:

	long MouseInputFilter(unsigned long actionType, unsigned long wParam, unsigned long lParam, bool& handled);
	long KeyboardInputFilter(unsigned long actionType, unsigned long wParam, unsigned long lParam, bool& handled);

private:

	void UpdateClick(unsigned long actionType, unsigned long wParam, unsigned long lParam);

	int GetCefMouseModifiers(WPARAM wparam) const;
	int GetCefKeyboardModifiers(WPARAM wparam, LPARAM lparam) const;
	bool IsKeyDown(int vk) const;
	bool IsKeyToggled(int vk) const;

private:

	CefBrowser* m_browser;

	int m_clickX, m_clickY;
	int m_clickCount;
	long m_clickTime;
	MouseButtonType m_clickMouseType;

	const unsigned int m_doubleClickInterval;
	const int m_doubleClickRange;
};

#endif // __INPUTHANDLER_H__