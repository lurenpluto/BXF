#ifndef __SVGRESCREATOR_H__
#define __SVGRESCREATOR_H__

#include "./SvgRes.h"

class SvgResCreator
    : public ExtResourceCreatorImpl<SvgRes>
{
public:
    SvgResCreator(void);
    virtual ~SvgResCreator(void);

private:

    // ExtResourceCreatorImpl
    virtual SvgRes* CreateResource(const char* lpResType, XLUE_RESOURCE_HANDLE hResHandle);
    virtual void DestroyResource(SvgRes* lpResObj);
};

#endif // __ICONRESCREATOR_H__