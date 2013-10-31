/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/
#include "stdafx.h"
#include "./WebKernelScriptIPCMessage.h"

const wchar_t WebKernelScriptIPCMessage::s_szJavascriptMessageHeader[] = L"xlue.javascript.message.";
const wchar_t WebKernelScriptIPCMessage::s_szJavascriptCallHeader[] = L"xlue.javascript.call.";
const wchar_t WebKernelScriptIPCMessage::s_szJavascriptCallbackHeader[] = L"xlue.javascript.callback.";

const wchar_t WebKernelScriptIPCMessage::s_szLuaMessageHeader[] = L"xlue.lua.message.";
const wchar_t WebKernelScriptIPCMessage::s_szLuaCallHeader[] = L"xlue.lua.call.";
const wchar_t WebKernelScriptIPCMessage::s_szLuaCallbackHeader[] = L"xlue.lua.callback.";

int WebKernelScriptIPCMessage::m_luaFunctionNumber = 0;
int WebKernelScriptIPCMessage::m_javascriptFunctionNumber = 0;