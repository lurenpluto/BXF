/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"

#include "./GaussianBlurDelegate.h"

#include <cmath>
#include <mmintrin.h>  //MMX
#include <xmmintrin.h> //SSE
#include <emmintrin.h> //SSE2
#include <pmmintrin.h> //SSE3
#include <tmmintrin.h> //SSSE3
#include <smmintrin.h> //SSE4.1
#include <nmmintrin.h> //SSE4.2
#include <omp.h>


/* Calcualte Gaussian Blur Filter Coefficiens
 *  alpha -> smooting gradient depends on sigma
 *  k = ((1-e^-alpha)^2)/(1+2*alpha*e^-alpha - e^-2alpha)
 *  a0 = k; a1 = k*(alpha-1)*e^-alpha; a2 = k*(alpha+1)*e^-alpha; a3 = -k*e^(-2*alpha)
 *  b1 = -2*e^-alpha; b2 = e^(-2*alpha)
 */
void CalGaussianCoeff( float sigma,  float *a0, float *a1, float *a2, float *a3, float *b1, float *b2, float *cprev, float *cnext)
{
  float alpha, lamma,  k; 
  // defensive check
  if (sigma < 0.5f)
	  sigma = 0.5f;

  alpha = (float) exp((0.726) * (0.726)) / sigma;
  lamma = (float)exp(-alpha);
  *b2 = (float)exp(-2 * alpha);
  k = (1 - lamma) * (1 - lamma) / (1 + 2 * alpha * lamma - (*b2));
  *a0 = k;
  *a1 = k * (alpha - 1) * lamma;
  *a2 = k * (alpha + 1) * lamma;
  *a3 = -k * (*b2);
  *b1 = -2 * lamma;
  *cprev = (*a0 + *a1) / (1 + *b1 + *b2);
  *cnext = (*a2 + *a3) / (1 + *b1 + *b2);
}

extern "C" void Horizontal_sse_iir_line(float *oTemp,  unsigned long* id, float *od, int width, int height, float *a0, float *a1, float *a2, float *a3, float *b1, float *b2, float *cprev, float *cnext);
extern "C" void Vertical_sse_iir_line(float *oTemp,  float* id, unsigned long *od, int width, int height, float *a0, float *a1, float *a2, float *a3, float *b1, float *b2, float *cprev, float *cnext);
// 这个方法的C++实现请看DericheIIRRender
// 这个方法的伪指令实现请看DericheIIRRenderSSEIntrinsics
// 这个方法的MMX实现还没有做
void DericheIIRRenderSSE(XL_BITMAP_HANDLE hBitmap, const float &sigma)
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo( &sysInfo );
	int nCPU = sysInfo.dwNumberOfProcessors;
	int threadNum = nCPU;
	omp_set_num_threads(threadNum);

	XLBitmapInfo bmp;
	XL_GetBitmapInfo(hBitmap, &bmp);

	assert(bmp.ColorType == XLGRAPHIC_CT_ARGB32);

	float a0, a1, a2, a3, b1, b2, cprev, cnext;
	CalGaussianCoeff(sigma, &a0, &a1, &a2, &a3, &b1, &b2, &cprev, &cnext);

	unsigned long *lpPixelBufferInitial = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, 0);
	unsigned long *lpRowInitial = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, 1);

	int bufferSizePerThread = (bmp.Width > bmp.Height ? bmp.Width : bmp.Height) * 4;
	float *oTemp = new float[bufferSizePerThread * threadNum];
	float *od = new float[bmp.Width * bmp.Height * 4];
	int scanLineLengthInPixel = bmp.ScanLineLength / 4;
	
#pragma omp parallel for 
	for (int row = 0; row < bmp.Height; ++row)
	{
		int tidx = omp_get_thread_num();
		unsigned long *lpRowInitial = lpPixelBufferInitial + scanLineLengthInPixel * row;
		float *lpColumnInitial = od + row * 4;
		float *oTempThread = oTemp + bufferSizePerThread * tidx;
		Horizontal_sse_iir_line(oTempThread, lpRowInitial, lpColumnInitial, bmp.Width, bmp.Height, &a0, &a1, &a2, &a3, &b1, &b2, &cprev, &cnext );
	}

	int columnLineLengthInBytes = bmp.Height * 4;
#pragma omp parallel for
	for (int col = 0; col < bmp.Width; ++col)
	{
		int tidx = omp_get_thread_num();
		unsigned long *lpColInitial = lpPixelBufferInitial + col;

		float *lpRowInitial = od + columnLineLengthInBytes * col;
		float *oTempThread = oTemp + bufferSizePerThread * tidx;
		Vertical_sse_iir_line(oTempThread, lpRowInitial, lpColInitial, scanLineLengthInPixel, bmp.Height, &a0, &a1, &a2, &a3, &b1, &b2, &cprev, &cnext);
	}

	delete []oTemp;
	delete []od;
}