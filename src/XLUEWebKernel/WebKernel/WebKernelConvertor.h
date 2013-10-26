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
*   Author      :   范飞龙
*   Create      :   2013-10-25
*   LastChange  :   2013-10-25
*   History     :	
*
*   Description :   CefV8Value和CefListValue、CefDictionaryValue相互转化辅助类
*
********************************************************************/ 
#ifndef __WEBKERNELCONVERTOR_H__
#define __WEBKERNELCONVERTOR_H__
	
class WebKernelConvertor
{
public:
	// Transfer a V8 value to a List value.
	static void CefV8Array2ListValue(CefRefPtr<CefV8Value> source, CefRefPtr<CefListValue> target);

	// Transfer a List value to a V8 value.
	static void CefListValue2V8Array(CefRefPtr<CefListValue> source, CefRefPtr<CefV8Value> target);

	// Transfer a V8 Json Object 2 a Dictionary value.
	static void CefV8JsonObject2DictionaryValue(CefRefPtr<CefV8Value>source,CefRefPtr<CefDictionaryValue> target);

	// Transfer a Dictionary 2 a V8 Json Object value.
	static void CefDictionaryValue2V8JsonObject(CefRefPtr<CefDictionaryValue> source,CefRefPtr<CefV8Value> target);
};


#endif //__WEBKERNERLCONVERTOR_H__

