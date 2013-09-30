#ifndef __SVGRESHOLDER_H__
#define __SVGRESHOLDER_H__

#include "./SvgRes.h"

class SvgResTraits
    : public ExtResTraits<SvgResTraits>
{
public:

    static const char* GetResType()
    {
        return XLUE_EXTRES_SVG;
    }
};

typedef BaseResHolder<SvgResTraits> IconResHolder;

#endif // __ICONRESHOLDER_H__