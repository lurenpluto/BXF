/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./GaussianBlurDelegate.h"
#include <cmath>
#include <omp.h>

const float pi = 3.14159265358979323846;

void GaussianFunctionInteger(float i_sigma, int & io_radius, short ** o_results, int shift)
{
	float *fWeights = new float[io_radius * 2 + 1];
	float fSum = 0;
	// float fFactor = 1.0/i_sigma/sqrt(2*pi); // later we'll scale the weights to sum in 2^shift, so fFactor is not necessary to sum up to 1
	for ( int i = 0; i < io_radius + 1; i++)
	{
		(fWeights)[i] = exp(0 - (i - io_radius) *(i - io_radius)/(2 * i_sigma * i_sigma));
		fSum += (fWeights)[i];
	}
	for (int i = io_radius + 1; i < io_radius * 2 + 1; i++)
	{
		(fWeights)[i] = (fWeights)[io_radius * 2 - i];
		fSum += (fWeights)[i];
	} // normal distribution weights

	int expectedSum = 1;
	while (shift > 0)
	{
		expectedSum *= 2;
		shift -= 1;
	}
	float tmpFactor = (float)expectedSum / fSum;
	int diameter = 2 * io_radius + 1;

	*o_results = new short[diameter];
	int sum = 0;
	int firstNonZero = -1;
	for (int i = 0; i < diameter; i++)
	{
		(*o_results)[i] = (short)(fWeights[i] * tmpFactor + 0.5);
		sum += (*o_results)[i];
		if ((*o_results)[i] > 0 && firstNonZero == -1)
		{
			firstNonZero = i;
		}
	}

	while(firstNonZero >= 1 && sum < expectedSum)
	{
		(*o_results)[firstNonZero - 1]++;
		(*o_results)[diameter-firstNonZero]++;
		sum += 2;
		firstNonZero--;
	}

	if (sum > expectedSum)
	{
		int diff = sum - expectedSum;
		int diffRadius = diff / 2;
		for ( int i = -diffRadius; i <= diffRadius; i++)
		{
			(*o_results)[io_radius + i]--;
			sum--;
		}
		if (diff %2 == 0)
		{
			(*o_results)[io_radius]++;
			sum++;
		}
	}

	if (sum < expectedSum)
	{
		int diff = expectedSum - sum;
		int diffRadius = diff / 2;
		for ( int i = -diffRadius; i <= diffRadius; i++)
		{
			(*o_results)[io_radius + i]++;
		}
		if (diff%2 == 0)
		{
			(*o_results)[io_radius]--;
		}
	}
	io_radius = io_radius - firstNonZero;
	delete []fWeights;
}

extern "C" void Horizontal_mmx_fir_line(int radius, int width, int height, short *weightInt, unsigned long *lpPixelBufferTemp, unsigned long *lpPixelBufferLine);
extern "C" void Vertical_mmx_fir_line(int radius, int width, int height, short *weightInt, unsigned long *lpPixelBufferDest, unsigned long *lpPixelBufferLine);
// 这个方法的C++版本请看OneDimentionRender
void OneDimentionRenderMMX(XL_BITMAP_HANDLE hBitmap, const float &i_sigma, int i_radius)
{
	assert(hBitmap);
	XLBitmapInfo bmp;
	XL_GetBitmapInfo(hBitmap, &bmp);

	assert(bmp.ColorType == XLGRAPHIC_CT_ARGB32);

	short *weightBufferInitial = NULL;
	short *weightInt = NULL;
	short *weights = NULL;
	// 对半径做矫正, 因为要右移8位丢失精度, 所以半径大于128的像素是么有意义的
	if (i_radius > 128)
	{
		i_radius = 128;
	}
	if (i_radius > bmp.Width / 2 - 1)
	{
		i_radius = bmp.Width / 2 - 1;
	}
	if (i_radius > bmp.Height / 2 - 1)
	{
		i_radius = bmp.Height / 2 - 1;
	}

	// TODO: 这里改一改, 太难看了. 
	int radius = i_radius;
	GaussianFunctionInteger(i_sigma, radius, &weightBufferInitial, 8);
	if (radius == 0)
	{
		radius = 1;
	}
	weightInt = weightBufferInitial + i_radius - radius;
	weights = weightInt;

	unsigned long *lpPixelBufferLine = NULL;
	unsigned long *lpPixelBufferInitial = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, 0);
	unsigned long *lpPixelBufferTempInitial = (unsigned long*)malloc(sizeof(unsigned long) * bmp.Height * bmp.Width);
	int scanLengthInDW = bmp.ScanLineLength / 4;

	unsigned long heightInBytes = bmp.Height * 4;
	unsigned long *lpPixelBufferTemp = lpPixelBufferTempInitial +  bmp.Height * (bmp.Width - 1);
	unsigned long *lpPixelBufferTempEnd = lpPixelBufferTempInitial +  bmp.Height * (bmp.Width - 1);
	
#pragma omp parallel for 
	for (int line = 0; line < bmp.Height; ++line)
	{
		lpPixelBufferLine = lpPixelBufferInitial + scanLengthInDW * line;
		lpPixelBufferTemp = lpPixelBufferTempEnd + line;
		Horizontal_mmx_fir_line(radius,  bmp.Width,  heightInBytes,  weightInt, lpPixelBufferTemp, lpPixelBufferLine);
	}

	unsigned long *lpPixelBufferDest;
	unsigned long *lpPixelBufferDestEnd = lpPixelBufferInitial + scanLengthInDW * (bmp.Height - 1);
	
#pragma omp parallel for 
	for (int column = 0; column < bmp.Width; ++column)
	{
		lpPixelBufferLine = lpPixelBufferTempInitial + column * bmp.Height; // 线头
		lpPixelBufferDest = lpPixelBufferDestEnd + column; // 线尾
		Vertical_mmx_fir_line(radius, bmp.ScanLineLength, bmp.Height, weightInt, lpPixelBufferDest, lpPixelBufferLine);
	}
	delete []weightBufferInitial;
	free(lpPixelBufferTempInitial);
}
