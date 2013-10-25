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
*   FileName    :   ListUtil.h
*   Author      :   ·¶·ÉÁú
*   Create      :   2013-10-25
*   LastChange  :   2013-10-25
*   History     :	
*
*   Description :   CefListValue¸¨Öúº¯Êý
*
********************************************************************/ 
#ifndef __LISTUTIL_H__
#define __LISTUTIL_H__

// Forward declarations.
void SetList(CefRefPtr<CefV8Value> source, CefRefPtr<CefListValue> target);

void SetList(CefRefPtr<CefListValue> source, CefRefPtr<CefV8Value> target);

// Transfer a V8 value to a List index.
void SetListValue(CefRefPtr<CefListValue> list, int index,CefRefPtr<CefV8Value> value);

// Transfer a V8 array to a List.
void SetList(CefRefPtr<CefV8Value> source, CefRefPtr<CefListValue> target);

// Transfer a List value to a V8 array index.
void SetListValue(CefRefPtr<CefV8Value> list, int index, CefRefPtr<CefListValue> value);

// Transfer a List to a V8 array.
void SetList(CefRefPtr<CefListValue> source, CefRefPtr<CefV8Value> target);

#endif //__LISTUTIL_H__

