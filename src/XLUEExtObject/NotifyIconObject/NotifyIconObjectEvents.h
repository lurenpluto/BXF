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
*   FileName    :   NotifyIconObjectEvents
*   Author      :   李亚星
*   Create      :   2013-10-14 
*   LastChange  :   2013-10-14
*   History     :	
*
*   Description :   NotifyIconObject的事件定义
*
********************************************************************/ 
#ifndef __NOTIFYICONOBJECTEVENTS_H__
#define __NOTIFYICONOBJECTEVENTS_H__

class NotifyIconObject;

class NotifyIconObjectEvents
	: public ExtObjEventImplEx<NotifyIconObjectEvents, NotifyIconObject>
{
private:

	typedef ExtObjEventImplEx<NotifyIconObjectEvents, NotifyIconObject> base_class;
	friend class base_class;

public:
	NotifyIconObjectEvents(XLUE_LAYOUTOBJ_HANDLE hOwner);
	virtual ~NotifyIconObjectEvents(void);

public:

	long OnContextMenu(long x, long y, unsigned long flags, bool &handled);
	long OnKeySelect(bool &handled);
	long OnSelect(bool &handled);

	long OnBalloonShow(bool &handled);
	long OnBalloonHide(bool &handled);
	long OnBalloonTimeout(bool &handled);
	long OnBalloonUserClick(bool &handled);

public:

	// ExtObjEventImplEx methods
	static NotifyIconObjectEvents* ExtEventObjFromObject(NotifyIconObject* lpObj);

private:

	DECLEAR_EXT_EVENT_VECTOR();

	DECLEAR_EXT_EVENT(OnContextMenu);
	DECLEAR_EXT_EVENT(OnKeySelect);
	DECLEAR_EXT_EVENT(OnSelect);
	
	DECLEAR_EXT_EVENT(OnBalloonShow);
	DECLEAR_EXT_EVENT(OnBalloonHide);
	DECLEAR_EXT_EVENT(OnBalloonTimeout);
	DECLEAR_EXT_EVENT(OnBalloonUserClick);

private:

	LayoutObjectWrapper m_owner;
	lua_State* m_luaState;
};

#endif // __NOTIFYICONOBJECTEVENTS_H__