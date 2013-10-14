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

    // 返回值不会增持引用计数
    wxSVGDocument* GetSVGHandle();

private:

    // ExtResourceMethodsImpl
    virtual bool LoadRes(const wchar_t* lpResFolder);
    virtual bool FreeRes();

    // 返回值不需增加引用计数！！
    virtual void* GetRealHandle();

    // 真正资源句柄的生命周期基于引用计数管理
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