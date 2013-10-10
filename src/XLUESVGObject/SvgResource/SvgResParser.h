#ifndef __SVGRESPARSER_H__
#define __SVGRESPARSER_H__

#include "./SvgRes.h"

class SVGResParser
    : public ExtResourceParserImplEx<SVGRes>
{
public:
    SVGResParser(void);
    virtual ~SVGResParser(void);

private:

    // ExtResourceParserImpl
    virtual bool ParseAttributeFromXML(SVGRes* lpResObj, const char* lpName, const char* lpValue);
    virtual bool ParseAttributeFromLua(SVGRes* lpResObj, const char* lpName, lua_State* luaState, int index);

};

#endif // __SVGRESPARSER_H__