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
*   FileName    :   NotifyIconObject
*   Author      :   李亚星
*   Create      :   2013-10-14 
*   LastChange  :   2013-10-14
*   History     :	
*
*   Description :   用以实现win32平台下，系统托盘图标功能的逻辑元对象
*
********************************************************************/ 
#ifndef __NOTIFYICONOBJECT_H__
#define __NOTIFYICONOBJECT_H__

#define EXTCLASSNAME_NOTIFYICONOBJECT "NotifyIconObject"

#include "../IconResource/IconResHolder.h"
#include "../../XLUELib/Window/SafeWindow.h"

class NotifyIconObject;

class NotifyIconWindow
	: public CWindowImpl<NotifyIconWindow>
{
public:

	enum 
	{
		UWM_NOTIFYICON_NOTIFY = WM_USER + 1024,
	};

public:
	NotifyIconWindow();
	virtual ~NotifyIconWindow();

	void SetOwner(NotifyIconObject* lpOwner);

private:

	BEGIN_MSG_MAP(NotifyIconWindow)
		MESSAGE_HANDLER(UWM_NOTIFYICON_NOTIFY, OnNotify)
		MESSAGE_HANDLER(s_taskbarCreateMsg, OnTaskbarCreate)
	END_MSG_MAP()

	LRESULT OnNotify(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTaskbarCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

private:

	static unsigned int s_taskbarCreateMsg;

	NotifyIconObject* m_lpOwner;
};

class NotifyIconObjectEvents;

class NotifyIconObject
	: public ExtLayoutObjMethodsImpl
	, public ExtObjImplSafeLock
{
private:

	enum NotifyIconStatus
	{
		NotifyIconStatus_added = 1,
		NotifyIconStatus_removed = 2,
	};

	typedef BaseResHolderEx<NotifyIconObject, IconResTraits> IconResHolderEx;
	
	typedef ExtObjImplAutoSafeLockT<NotifyIconObject> AutoSafeLock;

	friend class NotifyIconWindow;

public:
	NotifyIconObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~NotifyIconObject(void);

	NotifyIconObjectEvents* GetEventContainer();

	void SetIconResID(const char* resID);
	const char* GetIconResID() const;

	void SetIcon(XLUE_RESOURCE_HANDLE hResHandle);
	// 返回值不增持引用计数
	XLUE_RESOURCE_HANDLE GetIcon();

	void SetTip(const wchar_t* lpMessage);
	const wchar_t* GetTip();

	bool SetIconVisible(bool visible);
	bool GetIconVisible();

	bool ShowBalloonTip(const wchar_t* lpMessage, const wchar_t* lpTitle, unsigned int timeout, unsigned int iconFlags);

private:

	// ExtLayoutObjMethodsImpl
	virtual void OnInitControl();
	virtual void OnDestroy();
	virtual bool CanHandleInput();
	virtual void OnVisibleChange(BOOL bVisible);

private:

	// NotifyIconWindow call methods
	void OnNotify(WPARAM wParam, LPARAM lParam);
	void OnTaskbarCreate();

	// IconResHolder
	void OnIconResChange();

	HICON GetIconHandle();

	bool AddIcon();
	bool RemoveIcon();

	bool UpdateVisible();
	bool UpdateIcon();
	bool UpdateTip();

	bool UpdateInfo(const wchar_t* lpInfo, const wchar_t* lpTitle, unsigned int timeout, unsigned int flags);

	bool ProcessNormalInput(unsigned int msg);

	unsigned long GetKeyFlags() const;

private:

	SafeWindowWrapper<NotifyIconWindow>* m_lpNotifyWindow;

	IconResHolderEx m_icon;

	std::wstring m_message;

	NotifyIconStatus m_status;

	bool m_iconVisible;

	NotifyIconObjectEvents* m_lpEvents;
};

#endif // __NOTIFYICONOBJECT_H__