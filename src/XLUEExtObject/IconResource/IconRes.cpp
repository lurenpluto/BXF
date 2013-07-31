/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./IconRes.h"
#include <shlwapi.h>

IconRes::IconRes(XLUE_RESOURCE_HANDLE hResHandle)
:base_class(hResHandle),
m_resLoaded(false),
m_iconHandle(NULL),
m_sourceType(IconSourceType_unknown),
m_iconIndex(0),
m_cx(0),
m_cy(0)
{
}

IconRes::~IconRes(void)
{
	if (m_iconHandle != NULL)
	{
		FreeImpl();
	}
}

bool IconRes::LoadRes(const wchar_t* lpResFolder)
{
	assert(lpResFolder);
	assert(!m_resLoaded);
	
	if (lpResFolder != NULL)
	{
		m_resFolder = lpResFolder;
	}

	if (m_iconHandle != NULL)
	{
		FreeImpl();
	}

	m_resLoaded = true;
	
	bool ret = LoadImpl(lpResFolder);
	assert(ret);

	return ret;
}

bool IconRes::FreeRes()
{
	assert(m_resLoaded);
	m_resLoaded = false;

	if (m_iconHandle != NULL)
	{
		FreeImpl();
	}

	assert(m_iconHandle == NULL);

	return true;
}

bool IconRes::LoadImpl(const wchar_t* lpResFolder)
{
	assert(m_sourceType != IconSourceType_unknown);
	assert(m_iconHandle == NULL);
	assert(lpResFolder);

	std::wstring file;
	XLUETranscode::UTF8_to_Unicode(m_iconFile.c_str(), m_iconFile.size(), file);

	if (m_sourceType == IconSourceType_file || m_sourceType == IconSourceType_module)
	{
		if (::PathIsRelative(file.c_str()))
		{
			wchar_t szPath[_MAX_PATH];
			::PathCombine(szPath, lpResFolder, file.c_str());
			file = szPath;
		}
	}

	if (m_sourceType == IconSourceType_file)
	{
		m_iconHandle = XLGP_LoadIconFromFile(file.c_str(), m_cx, m_cy);
	}
	else if (m_sourceType == IconSourceType_ext)
	{
		m_iconHandle = XLGP_LoadIconFromFileExt(file.c_str(), m_cx, m_cy);
	}
	else if (m_sourceType == IconSourceType_module)
	{
		HMODULE hModule = ::LoadLibraryEx(file.c_str(), NULL, LOAD_LIBRARY_AS_DATAFILE);
		assert(hModule);
		if (hModule != NULL)
		{
			m_iconHandle = XLGP_LoadIconFromModule(hModule, m_iconIndex, m_cx, m_cy);
			::FreeLibrary(hModule);
		}
	}
	else
	{
		assert(false);
	}

	if (m_iconHandle == NULL)
	{
		return false;
	}

	return true;
}

XLGP_ICON_HANDLE IconRes::GetIconHandle()
{
	if (!m_resLoaded)
	{
		m_resLoaded = true;
		assert(!m_resFolder.empty());
		
		LoadImpl(m_resFolder.c_str());
	}

	return m_iconHandle;
}

void IconRes::FreeImpl()
{
	assert(m_iconHandle);
	if (m_iconHandle != NULL)
	{
		XLGP_ReleaseIcon(m_iconHandle);
		m_iconHandle = NULL;
	}
}

void IconRes::SetModule( const char* lpModule )
{
	assert(lpModule);
	assert(m_sourceType == IconSourceType_unknown);

	m_sourceType = IconSourceType_module;
	m_iconFile = lpModule;
}

void IconRes::SetFile( const char* lpFile )
{
	assert(lpFile);
	assert(m_sourceType == IconSourceType_unknown);

	m_sourceType = IconSourceType_file;
	m_iconFile = lpFile;
}

void IconRes::SetExt( const char* lpExt )
{
	assert(lpExt);
	assert(m_sourceType == IconSourceType_unknown);

	m_sourceType = IconSourceType_ext;
	m_iconFile = lpExt;
}

void IconRes::SetWidth( int cx )
{
	m_cx = cx;
}

void IconRes::SetHeight( int cy )
{
	m_cy = cy;
}

void IconRes::SetIconIndex( int index )
{
	m_iconIndex = index;
}

void* IconRes::GetRealHandle()
{
	return (void*)GetIconHandle();
}

long IconRes::AddRefRealHandle( void* lpRealHandle )
{
	assert(lpRealHandle);
	XLGP_ICON_HANDLE hIconHandle = (XLGP_ICON_HANDLE)lpRealHandle;

	return (long)XLGP_AddRefIcon(hIconHandle);
}

long IconRes::ReleaseRealHandle( void* lpRealHandle )
{
	assert(lpRealHandle);
	XLGP_ICON_HANDLE hIconHandle = (XLGP_ICON_HANDLE)lpRealHandle;

	return (long)XLGP_ReleaseIcon(hIconHandle);
}