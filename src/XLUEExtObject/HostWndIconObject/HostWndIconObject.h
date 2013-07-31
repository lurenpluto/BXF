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
*   FileName    :   HostWndIconObject
*   Author      :   李亚星
*   Create      :   2013-7-29 
*   LastChange  :   2013-7-29
*   History     :	
*
*   Description :   用以对hostwnd窗口提供icon支持的object
*
********************************************************************/ 
#ifndef __HOSTWNDICONOBJECT_H__
#define __HOSTWNDICONOBJECT_H__

#define EXTCLASSNAME_HOSTWNDICONOBJECT "HostWndIconObject"

#include "../IconResource/IconResHolder.h"

class HostWndIconObject
	: public ExtLayoutObjMethodsImpl
{
public:

	typedef BaseResHolderEx<HostWndIconObject, IconResTraits> IconResHolderEx;

public:
	HostWndIconObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~HostWndIconObject(void);

	void SetIconResID(const char* resID, bool big);
	const char* GetIconResID(bool big);

	void SetIcon(XLUE_RESOURCE_HANDLE hResHandle, bool big);
	// 返回值不增持引用计数
	XLUE_RESOURCE_HANDLE GetIcon(bool big);

private:

	// ExtLayoutObjMethodsImpl
	virtual void OnCreateHostWnd(XLUE_OBJTREE_HANDLE /*hTree*/, XLUE_HOSTWND_HANDLE hHostWnd, BOOL bCreate);

private:

	void ApplyIcon(HWND hWnd, bool big);
	void ApplyIconImpl(HWND hWnd, bool big);

	void OnBigIconResChange();
	void OnSmallIconResChange();

private:

	IconResHolderEx m_bigIcon, m_smallIcon;
	bool m_inApplying;
};

#endif // __HOSTWNDICONOBJECT_H__