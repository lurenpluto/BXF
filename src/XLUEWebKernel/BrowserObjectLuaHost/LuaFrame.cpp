/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaFrame.h"

#define XLUE_WEBKERNEL_LUAFRAME_CLASSNAME "Xunlei.UIEngine.BoltBrowser.Frame.Class"

XLLRTGlobalAPI LuaFrame::s_LuaFrameMemberFunctions[] = 
{
	{"__gc", LuaFrame::GC},

	{"Undo", LuaFrame::Undo},
	{"Redo", LuaFrame::Redo},
	{"Cut", LuaFrame::Cut},
	{"Copy", LuaFrame::Copy},
	{"Paste", LuaFrame::Paste},
	{"Delete", LuaFrame::Delete},
	{"SelectAll", LuaFrame::SelectAll},

	{"IsMain", LuaFrame::IsMain},
	{"IsFocused", LuaFrame::IsFocused},
	{"GetName", LuaFrame::GetName},

	{"GetParent", LuaFrame::GetParent},
	{"GetURL", LuaFrame::GetURL},
	{"GetBrowser", LuaFrame::GetBrowser},

	{NULL, NULL},
};

void LuaFrame::Register( XL_LRT_ENV_HANDLE hEnv )
{
	long result = XLLRT_RegisterClass(hEnv, XLUE_WEBKERNEL_LUAFRAME_CLASSNAME, s_LuaFrameMemberFunctions, NULL, 0);
	assert(result == 0); 
}

void LuaFrame::PushFrame( lua_State* luaState, CefFrame* lpFrame )
{
	if (lpFrame == NULL)
	{
		lua_pushnil(luaState);
	}
	else
	{
		LuaFrameData* lpData = new LuaFrameData();
		lpData->m_frameID = lpFrame->GetIdentifier();
		lpData->m_browserID = lpFrame->GetBrowser()->GetIdentifier();

		long ret = XLLRT_PushXLObject(luaState, XLUE_WEBKERNEL_LUAFRAME_CLASSNAME, lpData);
		assert(ret == XLLRT_RESULT_SUCCESS);
		if (ret != XLLRT_RESULT_SUCCESS)
		{
			lua_pushnil(luaState);
		}
	}
}

CefFrame* LuaFrame::CheckFrame( lua_State* luaState, int index )
{
	LuaFrameData** lplpFrameData = (LuaFrameData**)luaL_checkudata(luaState, index, XLUE_WEBKERNEL_LUAFRAME_CLASSNAME);
	if (lplpFrameData != NULL)
	{
		LuaFrameData* lpFrameData = *lplpFrameData;

		CefBrowser* lpBrowser = g_webKernelGlobal.m_browserManager.GetBrowserFromID(lpFrameData->m_browserID);
		if (lpBrowser != NULL)
		{
			CefFrame* lpFrame = lpBrowser->GetFrame(lpFrameData->m_frameID);

			return lpFrame;
		}
	}

	return NULL;
}

int LuaFrame::Undo( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		spFrame->Undo();
	}

	return 0;
}

int LuaFrame::Redo( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		spFrame->Redo();
	}

	return 0;
}

int LuaFrame::Cut( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		spFrame->Cut();
	}

	return 0;
}

int LuaFrame::Copy( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		spFrame->Copy();
	}

	return 0;
}

int LuaFrame::Paste( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		spFrame->Paste();
	}

	return 0;
}

int LuaFrame::Delete( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		spFrame->Delete();
	}

	return 0;
}

int LuaFrame::SelectAll( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		spFrame->SelectAll();
	}

	return 0;
}

int LuaFrame::GC( lua_State* luaState )
{
	LuaFrameData** lplpFrameData = (LuaFrameData**)luaL_checkudata(luaState, 1, XLUE_WEBKERNEL_LUAFRAME_CLASSNAME);
	if (lplpFrameData != NULL)
	{
		LuaFrameData* lpFrameData = *lplpFrameData;
		delete lpFrameData;
	}

	return 0;
}

int LuaFrame::IsMain( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		lua_pushboolean(luaState, spFrame->IsMain());

		return 1;
	}

	lua_pushboolean(luaState, 0);
	return 1;
}

int LuaFrame::IsFocused( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		lua_pushboolean(luaState, spFrame->IsFocused());

		return 1;
	}

	lua_pushboolean(luaState, 0);
	return 1;
}

int LuaFrame::GetName( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		CefString name = spFrame->GetName();
		WebKernelLuaHelper::PushCefString(luaState, name);

		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}

int LuaFrame::GetParent( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		CefRefPtr<CefFrame> frame = spFrame->GetParent();
		PushFrame(luaState, frame.get());

		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}

int LuaFrame::GetURL( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		CefString name = spFrame->GetURL();
		WebKernelLuaHelper::PushCefString(luaState, name);

		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}

int LuaFrame::GetBrowser( lua_State* luaState )
{
	CefRefPtr<CefFrame> spFrame = CheckFrame(luaState, 1);
	if (spFrame != NULL)
	{
		int browserID = spFrame->GetBrowser()->GetIdentifier();
		XLUE_LAYOUTOBJ_HANDLE hObj = g_webKernelGlobal.m_browserManager.GetOwnerObjFromID(browserID);
		assert(hObj);

		XLUE_PushObject(luaState, hObj);
		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}