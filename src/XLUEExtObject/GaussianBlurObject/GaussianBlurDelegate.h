/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#ifndef _GAUSSIANBLURDELEGATE_H_
#define _GAUSSIANBLURDELEGATE_H_

void DericheIIRRenderSSE(XL_BITMAP_HANDLE hBitmap, const float &sigma);
void OneDimentionRenderMMX(XL_BITMAP_HANDLE hBitmpa, const float &sigma, int radius);

#endif //_GAUSSIANBLURDELEGATE_H_