/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#ifndef _GAUSSIANBLURDELEGATE_H_
#define _GAUSSIANBLURDELEGATE_H_

//#define DEBUG

void DericheIIRRenderSSE(XL_BITMAP_HANDLE hBitmap, const float &sigma);
void OneDimentionRenderMMX(XL_BITMAP_HANDLE hBitmpa, const float &sigma, int radius);

#ifdef DEBUG
void DericheIIRRenderSSEIntrinsics(XL_BITMAP_HANDLE hBitmap, float m_sigma);
void DericheIIRRender(XL_BITMAP_HANDLE hBitmap, float m_sigma);
void TwoDimentionRender(XL_BITMAP_HANDLE hBitmap, float m_sigma, int m_radius);
void OneDimentionRender(XL_BITMAP_HANDLE hBitmap, float m_sigma, int m_radius);
void OneDimentionRenderSSE(XL_BITMAP_HANDLE hBitmap, float m_sigma, int m_radius);
#endif

#endif //_GAUSSIANBLURDELEGATE_H_