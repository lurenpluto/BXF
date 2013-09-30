/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./SvgResRegister.h"
#include "./SvgResCreator.h"
#include "./SvgResParser.h"
#include "./LuaSvgRes.h"

bool SvgResRegister::RegisterSvgRes()
{
    return ExtResourceRegisterHelper<SvgRes, SvgResCreator, SvgResParser, LuaSvgRes>::Register(XLUE_EXTRES_SVG, 0);
}
