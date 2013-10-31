/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/
#include "stdafx.h"
#include "./DBG.h"

void DBG(const wchar_t* message)
{
	MessageBox(NULL,(LPCWSTR)message,(LPCWSTR)L"DEBUG",MB_OK);
}

void DBG(const std::wstring& message)
{
	MessageBox(NULL,(LPCWSTR)message.c_str(),(LPCWSTR)L"DEBUG",MB_OK);
}

void DBG(const CefString& message)
{
	MessageBox(NULL,(LPCWSTR)message.c_str(),(LPCWSTR)L"DEBUG",MB_OK);
}