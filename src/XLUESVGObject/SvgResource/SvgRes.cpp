/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./SvgRes.h"
#include <shlwapi.h>

SvgRes::SvgRes(XLUE_RESOURCE_HANDLE hResHandle)
:base_class(hResHandle),
m_resLoaded(false),
m_pSvgDoc(NULL),
m_sourceType(SvgSourceType_unknown)
{
}

SvgRes::~SvgRes(void)
{
    if (m_pSvgDoc != NULL)
    {
        FreeImpl();
    }
}

bool SvgRes::LoadRes(const wchar_t* lpResFolder)
{
    assert(lpResFolder);
    assert(!m_resLoaded);

    if (lpResFolder != NULL)
    {
        m_resFolder = lpResFolder;
    }

    if (m_pSvgDoc != NULL)
    {
        FreeImpl();
    }

    m_resLoaded = true;

    bool ret = LoadImpl(lpResFolder);
    assert(ret);

    return ret;
}

bool SvgRes::FreeRes()
{
    assert(m_resLoaded);
    m_resLoaded = false;

    if (m_pSvgDoc != NULL)
    {
        FreeImpl();
    }

    assert(m_pSvgDoc == NULL);

    return true;
}

bool SvgRes::LoadImpl(const wchar_t* lpResFolder)
{
    assert(m_sourceType != SvgSourceType_unknown);
    assert(m_pSvgDoc == NULL);
    assert(lpResFolder);

    bool ret = false;

    std::wstring file;
    XLUETranscode::UTF8_to_Unicode(m_SvgFile.c_str(), m_SvgFile.size(), file);

    if (m_sourceType == SvgSourceType_file)
    {
        if (::PathIsRelative(file.c_str()))
        {
            wchar_t szPath[_MAX_PATH];
            ::PathCombine(szPath, lpResFolder, file.c_str());
            file = szPath;
        }
    }

    if (m_sourceType == SvgSourceType_file)
    {
        m_pSvgDoc = new wxSVGDocument();
        ret = m_pSvgDoc->Load(file);
    }
    else
    {
        assert(false);
    }

    return ret;
}

wxSVGDocument* SvgRes::GetSvgHandle()
{
    if (!m_resLoaded)
    {
        m_resLoaded = true;
        assert(!m_resFolder.empty());

        LoadImpl(m_resFolder.c_str());
    }

    return m_pSvgDoc;
}

void SvgRes::FreeImpl()
{
    assert(m_pSvgDoc);
    if (m_pSvgDoc != NULL)
    {
        delete m_pSvgDoc;
        m_pSvgDoc = NULL;
    }
}

void SvgRes::SetFile( const char* lpFile )
{
    assert(lpFile);
    assert(m_sourceType == SvgSourceType_unknown);

    m_sourceType = SvgSourceType_file;
    m_SvgFile = lpFile;
}

void* SvgRes::GetRealHandle()
{
    return (void*)GetSvgHandle();
}

long SvgRes::AddRefRealHandle( void* lpRealHandle )
{
    return 0;
}

long SvgRes::ReleaseRealHandle( void* lpRealHandle )
{
    return 0;
}