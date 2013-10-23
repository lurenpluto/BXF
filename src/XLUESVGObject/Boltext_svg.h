/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 

#ifdef BOLTEXT_SVG_EXPORTS
#define BOLTEXT_SVG_API __declspec(dllexport)
#else
#define BOLTEXT_SVG_API __declspec(dllimport)
#endif

#include <XLUE.h>
