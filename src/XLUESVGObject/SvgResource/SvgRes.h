/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 

#ifndef __ICONRES_H__
#define __ICONRES_H__

#include <bxf/ExtResourceImpl.h>
#include "svg/svg.h"

#define XLUE_EXTRES_SVG "svg"

using namespace Xunlei::Bolt;

class SVGRes
    : public ExtResourceMethodsImpl
{
public:

    enum SVGSourceType
    {
        SVGSourceType_unknown = 0,
        SVGSourceType_file = 1,
        SVGSourceType_string = 2,
    };

    typedef ExtResourceMethodsImpl base_class;

public:
    SVGRes(XLUE_RESOURCE_HANDLE hResHandle);
    ~SVGRes(void);

    void SetFile(const char* lpFile);

    // ����ֵ�����������ü���
    wxSVGDocument* GetSVGHandle();

private:

    // ExtResourceMethodsImpl
    virtual bool LoadRes(const wchar_t* lpResFolder);
    virtual bool FreeRes();

    // ����ֵ�����������ü�������
    virtual void* GetRealHandle();

    // ������Դ������������ڻ������ü�������
    virtual long AddRefRealHandle(void* /*lpRealHandle*/);
    virtual long ReleaseRealHandle(void* /*lpRealHandle*/);

private:

    bool LoadImpl(const wchar_t* lpResFolder);
    void FreeImpl();

private:

    bool m_resLoaded;
    bool m_resLoadRet;
    wxSVGDocument* m_pSVGDoc;

    SVGSourceType m_sourceType;
    std::string m_SVGFile;

    std::wstring m_resFolder;
};

#endif // __ICONRES_H__