/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./NotifyIconObjectEvents.h"
#include "./NotifyIconObject.h"

IMPL_EXT_EVENT(NotifyIconObjectEvents, OnContextMenu);
IMPL_EXT_EVENT(NotifyIconObjectEvents, OnKeySelect);
IMPL_EXT_EVENT(NotifyIconObjectEvents, OnSelect);

IMPL_EXT_EVENT(NotifyIconObjectEvents, OnBalloonShow);
IMPL_EXT_EVENT(NotifyIconObjectEvents, OnBalloonHide);
IMPL_EXT_EVENT(NotifyIconObjectEvents, OnBalloonTimeout);
IMPL_EXT_EVENT(NotifyIconObjectEvents, OnBalloonUserClick);

BEGIN_EXT_EVENT_VECTOR(NotifyIconObjectEvents)
	EXT_EVENT_ITEM(OnContextMenu)
	EXT_EVENT_ITEM(OnKeySelect)
	EXT_EVENT_ITEM(OnSelect)

	EXT_EVENT_ITEM(OnBalloonShow)
	EXT_EVENT_ITEM(OnBalloonHide)
	EXT_EVENT_ITEM(OnBalloonTimeout)
	EXT_EVENT_ITEM(OnBalloonUserClick)

END_EXT_EVENT_VECTOR()

NotifyIconObjectEvents::NotifyIconObjectEvents(XLUE_LAYOUTOBJ_HANDLE hOwner)
:m_owner(hOwner)
{
	assert(m_owner.IsValid());
	XL_LRT_ENV_HANDLE hEnv = XLLRT_GetEnv(NULL);
	XL_LRT_RUNTIME_HANDLE hRunTime = XLLRT_GetRuntime(hEnv, NULL);

	m_luaState = XLLRT_GetLuaState(hRunTime);
	assert(m_luaState);

	XLLRT_ReleaseRunTime(hRunTime);
	XLLRT_ReleaseEnv(hEnv);
}

NotifyIconObjectEvents::~NotifyIconObjectEvents(void)
{
	assert(m_luaState);
	m_luaState = NULL;

	assert(m_owner);
	m_owner = NULL;
}

long NotifyIconObjectEvents::OnContextMenu( long x, long y, unsigned long flags, bool &handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_owner);
	lua_pushinteger(luaState, x);
	lua_pushinteger(luaState, y);
	lua_pushinteger(luaState, flags);

	BOOL isHandled = FALSE;
	long ret = XLUE_FireExtObjEvent(m_owner, s_OnContextMenu, luaState, 4, 0, &isHandled);

	handled = !!isHandled;

	return ret;
}

long NotifyIconObjectEvents::OnKeySelect( bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_owner);

	BOOL isHandled = FALSE;
	long ret = XLUE_FireExtObjEvent(m_owner, s_OnKeySelect, luaState, 1, 0, &isHandled);

	handled = !!isHandled;

	return ret;
}

long NotifyIconObjectEvents::OnSelect( bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_owner);

	BOOL isHandled = FALSE;
	long ret = XLUE_FireExtObjEvent(m_owner, s_OnSelect, luaState, 1, 0, &isHandled);

	handled = !!isHandled;

	return ret;
}

long NotifyIconObjectEvents::OnBalloonShow( bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_owner);

	BOOL isHandled = FALSE;
	long ret = XLUE_FireExtObjEvent(m_owner, s_OnBalloonShow, luaState, 1, 0, &isHandled);

	handled = !!isHandled;

	return ret;
}

long NotifyIconObjectEvents::OnBalloonHide( bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_owner);

	BOOL isHandled = FALSE;
	long ret = XLUE_FireExtObjEvent(m_owner, s_OnBalloonHide, luaState, 1, 0, &isHandled);

	handled = !!isHandled;

	return ret;
}

long NotifyIconObjectEvents::OnBalloonTimeout( bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_owner);

	BOOL isHandled = FALSE;
	long ret = XLUE_FireExtObjEvent(m_owner, s_OnBalloonTimeout, luaState, 1, 0, &isHandled);

	handled = !!isHandled;

	return ret;
}

long NotifyIconObjectEvents::OnBalloonUserClick( bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_owner);

	BOOL isHandled = FALSE;
	long ret = XLUE_FireExtObjEvent(m_owner, s_OnBalloonUserClick, luaState, 1, 0, &isHandled);

	handled = !!isHandled;

	return ret;
}

NotifyIconObjectEvents* NotifyIconObjectEvents::ExtEventObjFromObject( NotifyIconObject* lpObj )
{
	assert(lpObj);

	return lpObj->GetEventContainer();
}