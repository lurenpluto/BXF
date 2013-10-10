#ifndef __SVGRESHOLDER_H__
#define __SVGRESHOLDER_H__

#include "./SvgRes.h"

class SVGResTraits
    : public ExtResTraits<SVGResTraits>
{
public:

    static const char* GetResType()
    {
        return XLUE_EXTRES_SVG;
    }
};

typedef BaseResHolder<SVGResTraits> SVGResHolder;

#endif // __ICONRESHOLDER_H__