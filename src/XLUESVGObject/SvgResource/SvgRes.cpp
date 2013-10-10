/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./SvgRes.h"
#include <shlwapi.h>

SVGRes::SVGRes(XLUE_RESOURCE_HANDLE hResHandle)
:base_class(hResHandle),
m_resLoaded(false),
m_pSVGDoc(NULL),
m_sourceType(SVGSourceType_unknown)
{
}

SVGRes::~SVGRes(void)
{
    if (m_pSVGDoc != NULL)
    {
        FreeImpl();
    }
}

bool SVGRes::LoadRes(const wchar_t* lpResFolder)
{
    assert(lpResFolder);

    if (lpResFolder != NULL)
    {
        m_resFolder = lpResFolder;
    }

    if (m_pSVGDoc != NULL)
    {
        FreeImpl();
    }

    bool ret = LoadImpl(lpResFolder);
    assert(ret);

    if (ret)
    {
        m_resLoaded = true;
    }

    return ret;
}

bool SVGRes::FreeRes()
{
    m_resLoaded = false;

    if (m_pSVGDoc != NULL)
    {
        FreeImpl();
    }

    assert(m_pSVGDoc == NULL);

    return true;
}

bool SVGRes::LoadImpl(const wchar_t* lpResFolder)
{
    assert(m_sourceType != SVGSourceType_unknown);
    assert(m_pSVGDoc == NULL);
    assert(lpResFolder);

    bool ret = false;

    std::wstring file;
    XLUETranscode::UTF8_to_Unicode(m_SVGFile.c_str(), m_SVGFile.size(), file);

    if (m_sourceType == SVGSourceType_file)
    {
        if (::PathIsRelative(file.c_str()))
        {
            wchar_t szPath[_MAX_PATH];
            ::PathCombine(szPath, lpResFolder, file.c_str());
            file = szPath;
        }
    }

    if (m_sourceType == SVGSourceType_file)
    {
        m_pSVGDoc = new wxSVGDocument();
        ret = m_pSVGDoc->Load(file);
    }
    else
    {
        assert(false);
    }

    if (!ret && m_pSVGDoc)
    {
        delete m_pSVGDoc;
        m_pSVGDoc = NULL;
    }

    return ret;
}

wxSVGDocument* SVGRes::GetSVGHandle()
{
    if (!m_resLoaded)
    {
        assert(!m_resFolder.empty());

        if (LoadImpl(m_resFolder.c_str()))
        {
            m_resLoaded = true;
        }
    }

    return m_pSVGDoc;
}

void SVGRes::FreeImpl()
{
    assert(m_pSVGDoc);
    if (m_pSVGDoc != NULL)
    {
        delete m_pSVGDoc;
        m_pSVGDoc = NULL;
    }
}

void SVGRes::SetFile( const char* lpFile )
{
    assert(lpFile);
    assert(m_sourceType == SVGSourceType_unknown);

    m_sourceType = SVGSourceType_file;
    m_SVGFile = lpFile;
}

void* SVGRes::GetRealHandle()
{
    return (void*)GetSVGHandle();
}

long SVGRes::AddRefRealHandle( void* lpRealHandle )
{
    return 0;
}

long SVGRes::ReleaseRealHandle( void* lpRealHandle )
{
    return 0;
}