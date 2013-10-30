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

#ifdef DEBUG
inline void AssignLongTo4Floats(float* out, unsigned long *in)
{
	unsigned int alpha = XLCOLOR_BGRA_A(*in);
	unsigned int green = XLCOLOR_BGRA_G(*in);
	unsigned int red = XLCOLOR_BGRA_R(*in);
	unsigned int blue = XLCOLOR_BGRA_B(*in);
	out[0] = (float)blue;
	out[1] = (float)green;
	out[2] = (float)red;
	out[3] = (float)alpha;
}

inline void Assign4FloatsToLong(unsigned long *out, float *in)
{
	unsigned int blue= in[0];
	unsigned int green = in[1];
	unsigned int red = in[2];
	unsigned int alpha = in[3];
	*out = XLCOLOR_BGRA(blue, green, red, alpha);
}

inline void Multi4Floats(float *out, float *in, float *coeff)
{
	out[0] = in[0] * (*coeff);
	out[1] = in[1] * (*coeff);
	out[2] = in[2] * (*coeff);
	out[3] = in[3] * (*coeff);
}
inline void Assign4Floats(float *out, float *in)
{
	out[0] = in[0];
	out[1] = in[1];
	out[2] = in[2];
	out[3] = in[3];
}
inline void Add4Floats(float *out, float *in_l, float *in_r)
{
	out[0] = in_l[0] + in_r[0];
	out[1] = in_l[1] + in_r[1];
	out[2] = in_l[2] + in_r[2];
	out[3] = in_l[3] + in_r[3];
}
inline void Sub4Floats(float *out, float *in_l, float *in_r)
{
	out[0] = in_l[0] - in_r[0];
	out[1] = in_l[1] - in_r[1];
	out[2] = in_l[2] - in_r[2];
	out[3] = in_l[3] - in_r[3];
}

/*
	Input:
	00,01,02 (*)
	10,11,12

	中间结果oTemp:
	00,01,02

	Output:
	(*)
	00,10
	01,11
	02,12

	width = 3;
	height = 2
*/
/*
	//for (int col = 0; col < width; col++)
	//{
	//	AssignLongTo4Floats(od, id);
	//	id += 1;
	//	od += height*4;
	//}
	//return;
*/
void DerichIIRHorizontal(float *oTemp,  unsigned long* id, float *od, int width, int height, int Nwidth, float *a0, float *a1, float *a2, float *a3, float *b1, float *b2, float *cprev, float *cnext)
{
	float prevIn[4];
	float currIn[4];
	float prevOut[4];
	float prev2Out[4];

	float currComp[4];
	float temp1[4];
	float temp2[4];
	float temp3[4];

	// 第一遍从左往右的公式是: oTemp[i] = (a0*id[i] + a1*id[i-1]) - (b1*oTemp[i-1] + b2*oTemp[i-2])
	// 第二遍从右往左的公式是: od[i] = oTemp[i] + (a3*id[i+1] + a4*id[i+2]) - (b1*od[i+1]+b2*od[i+2])
	AssignLongTo4Floats(prevIn, id);
	Multi4Floats(prevOut, prevIn, cprev);
	Assign4Floats(prev2Out, prevOut);
	for (int x = 0; x < width; ++x)
	{
		AssignLongTo4Floats(currIn, id);
		Multi4Floats(currComp, currIn, a0);
		Multi4Floats(temp1, prevIn, a1);
		Multi4Floats(temp2, prevOut, b1);
		Multi4Floats(temp3, prev2Out, b2);
		Add4Floats(currComp, currComp, temp1);
		Add4Floats(temp2, temp2, temp3);
		Assign4Floats(prev2Out, prevOut);
		Sub4Floats(prevOut, currComp, temp2);
		Assign4Floats(prevIn, currIn);

		Assign4Floats(oTemp, prevOut);
		oTemp += 4;
		id += 1;
	}
	id -= 1;
	od += 4 * height * (width - 1);// 最后一行行首
	oTemp -= 4;
	
	AssignLongTo4Floats(prevIn, id);
	Multi4Floats(prev2Out, prevIn, cnext);
	Assign4Floats(prevOut, prev2Out);
	Assign4Floats(currIn, prevIn);

	a0 = a2;
	a1 = a3;

	float inNext[4];
	float output[4];

	for (int x = width - 1; x >= 0; --x)
	{
		AssignLongTo4Floats(inNext, id);
		Assign4Floats(output, oTemp);

		Multi4Floats(currComp, currIn, a0);
		Multi4Floats(temp1, prevIn, a1);
		Multi4Floats(temp2, prevOut, b1);
		Multi4Floats(temp3, prev2Out, b2);
		Add4Floats(currComp, currComp, temp1);
		Add4Floats(temp2, temp2, temp3);
		Assign4Floats(prev2Out, prevOut);
		Sub4Floats(prevOut, currComp, temp2);
		Assign4Floats(prevIn, currIn);
		Assign4Floats(currIn, inNext);
		Add4Floats(output, output, prevOut);

		Assign4Floats(od, output);
		id -= 1;
		od -= 4 * height;
		oTemp -= 4;
	}
}

void DerichIIRHorizontalSSEIntrinsics(float *oTemp,  unsigned long* id, float *od, int width, int height, int Nwidth, float *a0, float *a1, float *a2, float *a3, float *b1, float *b2, float *cprev, float *cnext)
{
	__m128 prevIn, currIn, prevOut, prev2Out, coeft, coefa0, coefa1, coefb1, coefb2;

	coeft = _mm_load_ss((float*)cprev);
	coeft = _mm_shuffle_ps(coeft, coeft, 0x00);
	prevIn = _mm_cvtepi32_ps(_mm_cvtepu8_epi32(*(__m128i *) (id)));
	prev2Out = _mm_mul_ps(prevIn, coeft);
	prevOut = prev2Out;

	coefa0 = _mm_load_ss((float*)a0);
	coefa0 = _mm_shuffle_ps(coefa0, coefa0, 0x00);
	coefa1 = _mm_load_ss((float*)a1);
	coefa1 = _mm_shuffle_ps(coefa1, coefa1, 0x00);
	coefb1 = _mm_load_ss((float*)b1);
	coefb1 = _mm_shuffle_ps(coefb1, coefb1, 0x00);
	coefb2 = _mm_load_ss((float*)b2);
	coefb2 = _mm_shuffle_ps(coefb2, coefb2, 0x00);

	for (int x = 0; x < width; x++)
	{
		__m128 currIn = _mm_cvtepi32_ps(_mm_cvtepu8_epi32(*(__m128i*)(id)));
		__m128 currComp = _mm_mul_ps(currIn, coefa0);
		__m128 temp1 = _mm_mul_ps(prevIn, coefa1);
		__m128 temp2 = _mm_mul_ps(prevOut, coefb1);
		__m128 temp3 = _mm_mul_ps(prev2Out, coefb2);
		currComp= _mm_add_ps(currComp, temp1);
		temp2 = _mm_add_ps(temp2, temp3);
		prev2Out = prevOut;
		prevOut = _mm_sub_ps(currComp, temp2);
		prevIn = currIn;
		_mm_storeu_ps(oTemp, prevOut);
		id += 1;
		oTemp += 4;
	}

	id -= 1;
	od += 4 * height * (width - 1);//输出的最后一行, 不一定是行首, 当前输入行在原图中时第y行, 则od的位置应指向输出的最后一行的第y列, 见上图id, oTemp, od的转换关系
	oTemp -= 4;

	coeft = _mm_load_ss((float*)cnext);
	coeft = _mm_shuffle_ps(coeft, coeft, 0x00);
	prevIn = _mm_cvtepi32_ps(_mm_cvtepu8_epi32(*(__m128i *)(id)));
	prev2Out = _mm_mul_ps(prevIn, coeft);
	prevOut = prev2Out;
	currIn = prevIn;

	coefa0 = _mm_load_ss((float*)a2);
	coefa0 = _mm_shuffle_ps(coefa0, coefa0, 0x00);
	coefa1 = _mm_load_ss((float*)a3);
	coefa1 = _mm_shuffle_ps(coefa1, coefa1, 0x00);

	for (int x = width - 1; x >= 0; x--)
	{
		__m128 inNext = _mm_cvtepi32_ps(_mm_cvtepu8_epi32(*(__m128i*)(id)));
		__m128 output = _mm_loadu_ps((float*)(oTemp));
		__m128 currComp = _mm_mul_ps(currIn, coefa0);
		__m128 temp1 = _mm_mul_ps(prevIn, coefa1);
		__m128 temp2 = _mm_mul_ps(prevOut, coefb1);
		__m128 temp3 = _mm_mul_ps(prev2Out, coefb2);
		currComp = _mm_add_ps(currComp, temp1);
		temp2 = _mm_add_ps(temp2, temp3);
		prev2Out = prevOut;
		prevOut = _mm_sub_ps(currComp, temp2);
		prevIn = currIn;
		currIn = inNext;
		output = _mm_add_ps(output, prevOut);

		_mm_storeu_ps((float*)od, output);
		
		id -= 1;
		od -= 4 * height;
		oTemp -= 4;
	}
}
/*
	Input:
	00(id),	10
	01,		11
	02,		12

	Output:
	00(od),	01,02
	10,		11,12

	width:2
	height:3
*/
/*
	无模糊输出的结果应该是
	for (int col = 0; col < height; col++)
	{
		Assign4FloatsToLong(od, id);
		od += width;
		id += 4;
	}
	return;
*/
void DerichIIRVertical(float *oTemp, float *id, unsigned long *od, int height, int width, float *a0, float *a1, float *a2, float *a3, float *b1, float *b2, float *cprev, float *cnext)
{
	float prevIn[4];
	float currIn[4];
	float prevOut[4];
	float prev2Out[4];

	float currComp[4];
	float temp1[4];
	float temp2[4];
	float temp3[4];

	Assign4Floats(prevIn, id);
	Multi4Floats(prev2Out, prevIn, cprev);
	Assign4Floats(prevOut, prev2Out);

	for (int col = 0; col < height; col++)
	{
		Assign4Floats(currIn, id);

		Multi4Floats(currComp, currIn, a0);
		Multi4Floats(temp1, prevIn, a1);
		Multi4Floats(temp2, prevOut, b1);
		Multi4Floats(temp3, prev2Out, b2);

		Add4Floats(currComp, currComp, temp1);
		Add4Floats(temp2, temp2, temp3);
		Assign4Floats(prev2Out, prevOut);
		Sub4Floats(prevOut, currComp, temp2);
		Assign4Floats(prevIn, currIn);
		Assign4Floats(oTemp, prevOut);

		oTemp += 4;
		id += 4;
	}
	id -= 4;
	oTemp -= 4;
	od += width * (height - 1);

	a0 = a2;
	a1 = a3;
	Assign4Floats(prevIn, id);
	Assign4Floats(currIn, prevIn);
	Multi4Floats(prev2Out, prevIn, cnext);
	Assign4Floats(prevOut, prev2Out);

	float inNext[4];
	float output[4];
	for(int row = height - 1; row >= 0; row--)
	{
		Assign4Floats(inNext, id);
		Assign4Floats(output, oTemp);
		Multi4Floats(currComp, currIn, a0);
		Multi4Floats(temp1, prevIn, a1);
		Multi4Floats(temp2, prevOut, b1);
		Multi4Floats(temp3, prev2Out, b2);

		Add4Floats(currComp, currComp, temp1);
		Add4Floats(temp2, temp2, temp3);
		Assign4Floats(prev2Out, prevOut);
		Sub4Floats(prevOut, currComp, temp2);
		Assign4Floats(prevIn, currIn);
		Assign4Floats(currIn, inNext);

		Add4Floats(output, output, prevOut);
		Assign4FloatsToLong(od, output);
		
		id -= 4;
		od -= width;
		oTemp -= 4;
	}
}

void DerichIIRVerticalSSEIntrinsics(float *oTemp, float *id, unsigned long *od, int height, int width, float *a0, float *a1, float *a2, float *a3, float *b1, float *b2, float *cprev, float *cnext)
{
	__m128 prevIn, currIn, prevOut, prev2Out, coeft, coefa0, coefa1, coefb1, coefb2;

	coeft = _mm_load_ss((float*)cprev);
	coeft = _mm_shuffle_ps(coeft, coeft, 0x00);
	prevIn = _mm_loadu_ps((float*)id);
	prev2Out = _mm_mul_ps(prevIn, coeft);
	prevOut = prev2Out;

	coefa0 = _mm_load_ss((float*)a0);
	coefa0 = _mm_shuffle_ps(coefa0, coefa0, 0x00);
	coefa1 = _mm_load_ss((float*)a1);
	coefa1 = _mm_shuffle_ps(coefa1, coefa1, 0x00);
	coefb1 = _mm_load_ss((float*)b1);
	coefb1 = _mm_shuffle_ps(coefb1, coefb1, 0x00);
	coefb2 = _mm_load_ss((float*)b2);
	coefb2 = _mm_shuffle_ps(coefb2, coefb2, 0x00);

	for (int y = 0; y < height; y++)
	{
		currIn = _mm_loadu_ps((float*)id);
		__m128 currComp = _mm_mul_ps(currIn, coefa0);
		__m128 temp1 = _mm_mul_ps(prevIn, coefa1);
		__m128 temp2 = _mm_mul_ps(prevOut, coefb1);
		__m128 temp3 = _mm_mul_ps(prev2Out, coefb2);
		currComp = _mm_add_ps(currComp, temp1);
		temp2 = _mm_add_ps(temp2, temp3);
		prev2Out = prevOut;
		prevOut = _mm_sub_ps(currComp, temp2);
		prevIn = currIn;
		_mm_storeu_ps((float*)(oTemp), prevOut);

		id += 4;
		oTemp += 4;
	}

	id -= 4;
	oTemp -= 4;
	od += width * (height - 1);

	coeft = _mm_load_ss((float*)cnext);
	coeft = _mm_shuffle_ps(coeft, coeft, 0x00);
	prevIn = _mm_loadu_ps((float*)id);
	currIn = prevIn;
	prev2Out = _mm_mul_ps(prevIn, coeft);
	prevOut = prev2Out;

	coefa0 = _mm_load_ss((float*)a2);
	coefa0 = _mm_shuffle_ps(coefa0, coefa0, 0x00);
	coefa1 = _mm_load_ss((float*)a3);
	coefa1 = _mm_shuffle_ps(coefa1, coefa1, 0x00);

	for (int y = height - 1; y >= 0; y--)
	{
		__m128 inNext = _mm_loadu_ps((float*) id);
		__m128 output = _mm_loadu_ps((float*)(oTemp));
		__m128 currComp = _mm_mul_ps(currIn, coefa0);
		__m128 temp1 = _mm_mul_ps(prevIn, coefa1);
		__m128 temp2 = _mm_mul_ps(prevOut, coefb1);
		__m128 temp3 = _mm_mul_ps(prev2Out, coefb2);
		currComp = _mm_add_ps(currComp, temp1);
		temp2 = _mm_add_ps(temp2, temp3);
		prev2Out = prevOut;
		prevOut = _mm_sub_ps(currComp, temp2);
		prevIn = currIn;
		currIn = inNext;
		output = _mm_add_ps(output, prevOut);
		__m128i outputi = _mm_cvttps_epi32(output);

		outputi = _mm_packus_epi32(outputi, outputi);
		outputi = _mm_packus_epi16(outputi, outputi);
		//_mm_storel_epi64((__m128i *)od, outputi);//crash. bitmap damaged
		// TODO: You should not reference the internal raw data directly. Get your way to fix it!
		*od = outputi.m128i_i32[0];

		id -= 4;
		od -= width;
		oTemp -= 4;
	}
}

void DericheIIRRenderSSEIntrinsics(XL_BITMAP_HANDLE hBitmap, float m_sigma)
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
	CalGaussianCoeff(m_sigma, &a0, &a1, &a2, &a3, &b1, &b2, &cprev, &cnext);

	unsigned long *lpPixelBufferInitial = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, 0);
	unsigned long *lpRowInitial = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, 1);

	int bufferSizePerThread = (bmp.Width > bmp.Height ? bmp.Width : bmp.Height) * 4;
	float *oTemp = new float[bufferSizePerThread * threadNum];
	float *od = new float[bmp.Width * bmp.Height * 4];
	
#pragma omp parallel for 
	for (int row = 0; row < bmp.Height; ++row)
	{
		int tidx = omp_get_thread_num();
		unsigned long *lpRowInitial = lpPixelBufferInitial + bmp.ScanLineLength / 4 * row;
		float *lpColumnInitial = od + row * 4;
		float *oTempThread = oTemp + bufferSizePerThread * tidx;
		DerichIIRHorizontalSSEIntrinsics(oTempThread, lpRowInitial, lpColumnInitial, bmp.Width, bmp.Height, bmp.Width, &a0, &a1, &a2, &a3, &b1, &b2, &cprev, &cnext );
	}

// to make this omp parallel work, please enable project property->c++->language->OpenMP support
#pragma omp parallel for
	for (int col = 0; col < bmp.Width; ++col)
	{
		int tidx = omp_get_thread_num();
		/*
		原图buffer作为输出指针
		00(COL=0),	01(col=1),	02(col=2)
		10,			11,			12
		*/
		unsigned long *lpColInitial = lpPixelBufferInitial + col;
		//unsigned long *lpColInitial = (unsigned long*)XL_GetBitmapBuffer(hBitmap, col, 0);
		/*
		od作为输入指针
		00, 10
		01, 11
		02, 12
		*/
		float *lpRowInitial = od+bmp.Height * col * 4;
		float *oTempThread = oTemp + bufferSizePerThread * tidx;
		DerichIIRVerticalSSEIntrinsics(oTempThread, lpRowInitial, lpColInitial, bmp.Height, bmp.ScanLineLength/4, &a0, &a1, &a2, &a3, &b1, &b2, &cprev, &cnext);
	}

	delete []oTemp;
	delete []od;
}

void DericheIIRRender(XL_BITMAP_HANDLE hBitmap, float m_sigma)
{
	XLBitmapInfo bmp;
	XL_GetBitmapInfo(hBitmap, &bmp);

	assert(bmp.ColorType == XLGRAPHIC_CT_ARGB32);

	float a0, a1, a2, a3, b1, b2, cprev, cnext;
	CalGaussianCoeff(m_sigma, &a0, &a1, &a2, &a3, &b1, &b2, &cprev, &cnext);

	unsigned long *lpPixelBufferInitial = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, 0);
	unsigned long *lpRowInitial = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, 1);

	int bufferSizePerThread = (bmp.Width > bmp.Height ? bmp.Width : bmp.Height) * 4;
	float *oTemp = new float[bufferSizePerThread];
	float *od = new float[bmp.Width * bmp.Height * 4];
	
	for (int row = 0; row < bmp.Height; ++row)
	{
		unsigned long *lpRowInitial = lpPixelBufferInitial + bmp.ScanLineLength / 4 * row;
		float *lpColumnInitial = od + row * 4;
		DerichIIRHorizontal(oTemp, lpRowInitial, lpColumnInitial, bmp.Width, bmp.Height, bmp.Width, &a0, &a1, &a2, &a3, &b1, &b2, &cprev, &cnext );
	}

	for (int col = 0; col < bmp.Width; ++col)
	{
		int tidx = omp_get_thread_num();
		unsigned long *lpColInitial = lpPixelBufferInitial + col;
		float *lpRowInitial = od + bmp.Height * col * 4;
		DerichIIRVertical(oTemp, lpRowInitial, lpColInitial, bmp.Height, bmp.ScanLineLength/4, &a0, &a1, &a2, &a3, &b1, &b2, &cprev, &cnext);
	}

	delete []oTemp;
	delete []od;
}
#endif