// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define _WIN32_WINNT 0x0501		// winxp&win2003及以后的操作系统
#define _WIN32_IE 0x0600		// IE6以及以后的版本

#define  _CRT_SECURE_NO_WARNINGS

// Windows Header Files:
#include <windows.h>

#include <BXF/BXF.h>

#include "../XLUELib/XLUELib.h"

using namespace Xunlei::Bolt;