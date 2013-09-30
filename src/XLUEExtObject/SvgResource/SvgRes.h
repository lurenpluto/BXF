#ifndef __ICONRES_H__
#define __ICONRES_H__

#include <bxf/ExtResourceImpl.h>
#include "../wxsvg_vs2008/src/svg.h"

#define XLUE_EXTRES_SVG "svg"

using namespace Xunlei::Bolt;

class SvgRes
    : public ExtResourceMethodsImpl
{
public:

    enum SvgSourceType
    {
        SvgSourceType_unknown = 0,
        SvgSourceType_file = 1,
        SvgSourceType_string = 2,
    };

    typedef ExtResourceMethodsImpl base_class;

public:
    SvgRes(XLUE_RESOURCE_HANDLE hResHandle);
    ~SvgRes(void);

    void SetFile(const char* lpFile);

    // 返回值不会增持引用计数
    wxSVGDocument* GetSvgHandle();

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
    wxSVGDocument* m_pSvgDoc;

    SvgSourceType m_sourceType;
    std::string m_SvgFile;

    std::wstring m_resFolder;
};

#endif // __ICONRES_H__