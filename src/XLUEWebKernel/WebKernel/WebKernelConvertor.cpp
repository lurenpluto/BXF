/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/
#include "stdafx.h"
#include "./WebKernelConvertor.h"
#include "./DBG.h"


void WebKernelConvertor::CefV8Array2ListValue(CefRefPtr<CefV8Value> source, CefRefPtr<CefListValue> target) 
{
	assert(source->IsArray());

	int arg_length = source->GetArrayLength();
	if (arg_length == 0)
		return;

	// Start with null types in all spaces.
	target->SetSize(arg_length);
	
	for (int i = 0; i < arg_length; ++i)
	{
		CefRefPtr<CefV8Value> value = source->GetValue(i);
		if (value->IsBool())
		{
			target->SetBool(i, value->GetBoolValue());
		} 
		else if (value->IsInt()||value->IsUInt()) 
		{
			target->SetInt(i, value->GetIntValue());
		}
		else if (value->IsDouble()) 
		{
			target->SetDouble(i, value->GetDoubleValue());
		}
		else if (value->IsNull())
		{
			target->SetNull(i);
		}
		else if (value->IsString()||value->IsDate()) 
		{
			target->SetString(i, value->GetStringValue());
		} 
		else if (value->IsArray())
		{
			CefRefPtr<CefListValue> new_list = CefListValue::Create();
			CefV8Array2ListValue(value, new_list);
			target->SetList(i, new_list);
		}
		else if (value->IsObject())
		{
			CefRefPtr<CefDictionaryValue> new_dictionary = CefDictionaryValue::Create();
			CefV8JsonObject2DictionaryValue(value,new_dictionary);
			target->SetDictionary(i,new_dictionary);
		}
	}
}

void WebKernelConvertor::CefListValue2V8Array(CefRefPtr<CefListValue> source, CefRefPtr<CefV8Value> target) {
	assert(target->IsArray());

	int arg_length = static_cast<int>(source->GetSize());
	if (arg_length == 0)
		return;

	for (int i = 0; i < arg_length; ++i)
	{
		CefRefPtr<CefV8Value> new_value;

		CefValueType type = source->GetType(i);
		switch (type)
		{
		case VTYPE_BOOL:
			new_value = CefV8Value::CreateBool(source->GetBool(i));
			break;
		case VTYPE_DOUBLE:
			new_value = CefV8Value::CreateDouble(source->GetDouble(i));
			break;
		case VTYPE_INT:
			new_value = CefV8Value::CreateInt(source->GetInt(i));
			break;
		case VTYPE_STRING:
			new_value = CefV8Value::CreateString(source->GetString(i));
			break;
		case VTYPE_NULL:
			new_value = CefV8Value::CreateNull();
			break;
		case VTYPE_LIST:
			{
				CefRefPtr<CefListValue> list = source->GetList(i);
				new_value = CefV8Value::CreateArray(static_cast<int>(list->GetSize()));
				CefListValue2V8Array(list, new_value);
			}
			break;
		case VTYPE_DICTIONARY:
			{
				CefRefPtr<CefDictionaryValue> dictionary = source->GetDictionary(i);
				new_value = CefV8Value::CreateObject(NULL);
				CefDictionaryValue2V8JsonObject(dictionary,new_value);
			}
			break;
		default:
			break;
		}

		if (new_value.get()) 
		{
			target->SetValue(i, new_value);
		} 
		else
		{
			target->SetValue(i, CefV8Value::CreateNull());
		}
	}
}

void WebKernelConvertor::CefV8JsonObject2DictionaryValue(CefRefPtr<CefV8Value>source,CefRefPtr<CefDictionaryValue> target)
{
	assert(source->IsObject());

	std::vector<CefString> keys;
	source->GetKeys(keys);
	std::vector<CefString>::const_iterator beg = keys.begin();
	std::vector<CefString>::const_iterator end = keys.end();
	for (std::vector<CefString>::const_iterator it=beg;it!=end;++it)
	{
		const CefString key = *it;
		CefRefPtr<CefV8Value> value = source->GetValue(key);
		
		if (value->IsBool())
		{
			target->SetBool(key,value->GetBoolValue());
		}
		else if (value->IsDouble())
		{
			target->SetDouble(key,value->GetDoubleValue());
		}
		else if (value->IsInt()||value->IsUInt())
		{
			target->SetInt(key,value->GetIntValue());
		}
		else if (value->IsNull())
		{
			target->SetNull(key);
		}
		else if (value->IsString()||value->IsDate())
		{
			target->SetString(key,value->GetStringValue());
		}
		else if (value->IsArray())
		{
			CefRefPtr<CefListValue> listValue = CefListValue::Create();
			CefV8Array2ListValue(value,listValue);
			target->SetList(key,listValue);
		}
		else if (value->IsObject())
		{
			CefRefPtr<CefDictionaryValue> dictionaryValue=CefDictionaryValue::Create();
			CefV8JsonObject2DictionaryValue(value,dictionaryValue);
			target->SetDictionary(key,dictionaryValue);
		}
	}
}

void WebKernelConvertor::CefDictionaryValue2V8JsonObject(CefRefPtr<CefDictionaryValue> source,CefRefPtr<CefV8Value> target)
{
	assert(target->IsObject());
	
	CefDictionaryValue::KeyList keys;
	source->GetKeys(keys);
	CefDictionaryValue::KeyList::const_iterator beg = keys.begin();
	CefDictionaryValue::KeyList::const_iterator end = keys.end();
	
	for (CefDictionaryValue::KeyList::const_iterator it=beg;it!=end;++it)
	{
		CefRefPtr<CefV8Value> new_value;
		CefString key = *it;
		CefValueType type = source->GetType(key);

		switch (type)
		{
		case VTYPE_BOOL:
			new_value = CefV8Value::CreateBool(source->GetBool(key));
			break;
		case VTYPE_DOUBLE:
			new_value = CefV8Value::CreateDouble(source->GetDouble(key));
			break;
		case VTYPE_INT:
			new_value = CefV8Value::CreateInt(source->GetInt(key));
			break;
		case VTYPE_STRING:
			new_value = CefV8Value::CreateString(source->GetString(key));
			break;
		case VTYPE_NULL:
			new_value = CefV8Value::CreateNull();
			break;
		case VTYPE_LIST:
			{
				CefRefPtr<CefListValue> list = source->GetList(key);
				new_value = CefV8Value::CreateArray(static_cast<int>(list->GetSize()));
				CefListValue2V8Array(list, new_value);
			}
			break;
		case VTYPE_DICTIONARY:
			{
				CefRefPtr<CefDictionaryValue> dictionary = source->GetDictionary(key);
				new_value = CefV8Value::CreateObject(NULL);
				CefDictionaryValue2V8JsonObject(dictionary,new_value);
			}
			break;
		default:
			break;
		}
		if(new_value.get())
		{
			target->SetValue(key,new_value,V8_PROPERTY_ATTRIBUTE_NONE);
		}
		else
		{
			target->SetValue(key,CefV8Value::CreateNull(),V8_PROPERTY_ATTRIBUTE_NONE);
		}
	}
}
