// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <atlbase.h>
#include <atlstr.h>
#include <BXF/BXF.h>

#include "../XLUELib/XLUELib.h"

#include <include/cef_app.h>
#include <include/cef_render_handler.h>
#include <include/cef_client.h>

#include "./BrowserObjectLuaHost/WebKernelLuaHelper.h"
#include "./WebKernel/WebKernelGlobal.h"

using namespace Xunlei::Bolt;