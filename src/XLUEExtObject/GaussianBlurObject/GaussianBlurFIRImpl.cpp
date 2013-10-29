#include "stdafx.h"
#include "GaussianBlurDelegate.h"
#include <cmath>
#include <omp.h>

#include <time.h>

void GaussianFunction(double sigma, int r, float ** results);
void GaussianFunction2(double sigma, int r, double **results);
const double pi = 3.14159265358979323846;

void GaussianFunctionInteger(double i_sigma, int & io_radius, __int16 ** o_results, int shift)
{
	clock_t time1 = clock();
	float *fWeights;

	fWeights =new float[io_radius*2+1];
	float fSum = 0;
	// float fFactor = 1.0/i_sigma/sqrt(2*pi); // later we'll scale the weights to sum in 2^shift, so fFactor is not necessary to sum up to 1
	for ( int i=0; i < io_radius+1; i++)
	{
		(fWeights)[i] = exp(0- (i-io_radius)*(i-io_radius)/(2*i_sigma*i_sigma));
		fSum += (fWeights)[i];
	}
	for (int i = io_radius+1; i < io_radius*2+1; i++)
	{
		(fWeights)[i] = (fWeights)[io_radius*2-i];
		fSum += (fWeights)[i];
	} // normal distribution weights

	int expectedSum = 1;
	while (shift > 0)
	{
		expectedSum *= 2;
		shift -= 1;
	}
	float tmpFactor = (float)expectedSum/fSum;
	int diameter = 2*io_radius + 1;

	*o_results = new __int16[diameter];
	__int16 watch[9999];
	int sum = 0;
	int firstNonZero = -1;
	for (int i = 0; i < diameter; i++)
	{
		(*o_results)[i] = (__int16)(fWeights[i]*tmpFactor + 0.5);
		sum += (*o_results)[i];
		watch[i] = (*o_results)[i];
		if ((*o_results)[i] > 0 && firstNonZero == -1)
		{
			firstNonZero = i;
		}
	}

	while(firstNonZero >= 1 && sum < expectedSum)
	{
		(*o_results)[firstNonZero - 1]++;
		watch[firstNonZero-1] = (*o_results)[firstNonZero - 1];
		(*o_results)[diameter-firstNonZero]++;
		watch[diameter-firstNonZero] = (*o_results)[diameter-firstNonZero];
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
			watch[io_radius + i] = (*o_results)[io_radius + i];
			sum--;
		}
		if (diff %2 == 0)
		{
			(*o_results)[io_radius]++;
			sum++;
			watch[io_radius ] = (*o_results)[io_radius];
		}
	}

	if (sum <expectedSum)
	{
		int diff = expectedSum - sum;
		int diffRadius = diff / 2;
		for ( int i = -diffRadius; i <= diffRadius; i++)
		{
			(*o_results)[io_radius + i]++;
			watch[io_radius + i] = (*o_results)[io_radius + i];
		}
		if (diff%2 == 0)
		{
			(*o_results)[io_radius]--;
			watch[io_radius] = (*o_results)[io_radius];
		}
	}
	io_radius = io_radius - firstNonZero;
	delete []fWeights;
	clock_t time2=clock();
	float diff = (((float)time2 - (float)time1) / 1000000.0F ) * 1000; 
}

extern "C" void horizontal_mmx_fir_line(__int32 radius, __int32 width, __int32 height, __int16 *weightInt, unsigned long *lpPixelBufferTemp, unsigned long *lpPixelBufferLine);
extern "C" void vertical_mmx_fir_line(__int32 radius, __int32 width, __int32 height, __int16 *weightInt, unsigned long *lpPixelBufferDest, unsigned long *lpPixelBufferLine);
// ���������C++�汾�뿴OneDimentionRender
void OneDimentionRenderMMX(XL_BITMAP_HANDLE hBitmap, double i_sigma, __int32 i_radius)
{
	assert(hBitmap);
	XLBitmapInfo bmp;
	XL_GetBitmapInfo(hBitmap, &bmp);

	assert(bmp.ColorType == XLGRAPHIC_CT_ARGB32);

	__int16 *weightBufferInitial;
	__int16 *weightInt, *weights;
	if (i_radius > 128)
	{
		i_radius = 128;
	}
	// TODO: �����һ��, ̫�ѿ���. 
	__int32 radius = i_radius;
	GaussianFunctionInteger(i_sigma, radius, &weightBufferInitial, 8);
	if (radius == 0)
	{
		radius = 1;
	}
	weightInt = weightBufferInitial + i_radius - radius;
	weights = weightInt;

	unsigned long *lpPixelBufferLine;
	unsigned long *lpPixelBufferInitial = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, 0);
	unsigned long *lpPixelBufferTempInitial = (unsigned long*)malloc(sizeof(unsigned long)*bmp.Height*bmp.Width);
	__int32 scanLengthInDW = bmp.ScanLineLength/4;

	unsigned long heightInBytes = bmp.Height * 4;
	unsigned long *lpPixelBufferTemp = lpPixelBufferTempInitial +  bmp.Height * (bmp.Width - 1);
	unsigned long *lpPixelBufferTempEnd = lpPixelBufferTempInitial +  bmp.Height * (bmp.Width - 1);
	
#pragma omp parallel for 
	for (int line = 0; line < bmp.Height; ++line)
	{
		lpPixelBufferLine = lpPixelBufferInitial + scanLengthInDW*line;
		lpPixelBufferTemp = lpPixelBufferTempEnd + line;
		horizontal_mmx_fir_line(radius,  bmp.Width,  heightInBytes,  weightInt, lpPixelBufferTemp, lpPixelBufferLine);
	}

	unsigned long *lpPixelBufferDest;
	unsigned long *lpPixelBufferDestEnd = lpPixelBufferInitial + scanLengthInDW * (bmp.Height - 1);
	
#pragma omp parallel for 
	for (int column = 0; column < bmp.Width; ++column)
	{
		lpPixelBufferLine = lpPixelBufferTempInitial + column * bmp.Height; // ��ͷ
		lpPixelBufferDest = lpPixelBufferDestEnd + column; // ��β
		vertical_mmx_fir_line(radius, bmp.ScanLineLength, bmp.Height, weightInt, lpPixelBufferDest, lpPixelBufferLine);
	}
	delete []weightBufferInitial;
	free(lpPixelBufferTempInitial);
}

void OneDimentionRenderSSE(XL_BITMAP_HANDLE hBitmap, double m_sigma, __int32 m_radius)
{
	__int16 red = 256;
	__int16 red2 = red<<6;
	assert(hBitmap);
	XLBitmapInfo bmp;
	XL_GetBitmapInfo(hBitmap, &bmp);

	assert(bmp.ColorType == XLGRAPHIC_CT_ARGB32);

	__int32 diameter = m_radius * 2 + 1;
	float *weight;
	GaussianFunction(m_sigma, m_radius, &weight);

	unsigned long *lpPixelBufferLine;
	unsigned long *lpPixelBufferInitial = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, 0);
	unsigned long *lpPixelBufferTempInitial = (unsigned long*)malloc(sizeof(unsigned long)*bmp.Height*bmp.Width);

	__int32 lo = 0;
	__int32 hi = 0;
	lo = 0;
	hi = bmp.Width - 1;

	for (int line = 0; line < bmp.Height; ++line)
	{
		lpPixelBufferLine = lpPixelBufferInitial + bmp.ScanLineLength/4*line;
		unsigned long *lpPixelBufferTemp = lpPixelBufferTempInitial + line;
		for (__int32 col = 0; col < bmp.Width; ++col)
		{
			_asm{
				mov edx, diameter;
				mov ecx, weight;��ecxָ��weight���׵�ַ, ÿ��ѭ����4byte(1��float��ô��)ָ��weight[m_radius+j];
start_loop_h:
				; ��ʼѭ����
				mov ebx, m_radius;
				sub ebx, edx;
				add ebx, 1; // ����bx = j
				add ebx, col; // now bx = col + j

				cmp ebx, lo;
				jge gt_than_low_h;
				mov ebx, lo;
gt_than_low_h:
				cmp ebx, hi;
				jle ls_than_high_h;
				mov ebx, hi;
ls_than_high_h:
				;��������, ebx�������ȷ������ ��col+j��������0-width֮��

				; ���׵�ַ����eax, offset����ebx, offset*dword����������eax, ��eax����ĵ�ַȡֵ,
				; �����������µ��ǲ�֪��Ϊʲô mov lpPixelBufferLine, [dword eax + indx]������
				; Todo: Ч��?
				mov eax, lpPixelBufferLine; 
				imul ebx, 4;
				add eax, ebx; 

				; ��pixelbuffer���ĸ�8bit integer��չ��4��16bit integer, ����64bit�Ĵ���mmx0�� 
				pmovzxbd xmm0, [eax];
				cvtdq2ps xmm0, xmm0; eax������

				movd xmm1, [ecx]; ����xmm1�ĵ���λ���weight[m_radius+j]��
				shufps xmm1, xmm1, 0x00;
				mulps xmm0, xmm1;

				addps xmm2, xmm0;

				; ����ѭ����
				add ecx, 4;
				dec edx;
				jnz start_loop_h;

				mov esi, lpPixelBufferTemp; esi now points at destination

				; ��Ҫ��xmm2��ÿһ��floatȡ���س�byte,ƴ��һ��long
				cvtps2dq xmm2, xmm2;
				packssdw xmm2, xmm2;
				pextrw [esi], xmm2, 0;
				pextrw [esi+1], xmm2, 1;
				pextrw [esi+2], xmm2, 2;
				;pextrw [esi+3], xmm2, 3;
				mov [esi+3], 0xfe;

				emms;
			}
			lpPixelBufferTemp += bmp.Height;
		}
	}

	lo = 0;
	hi = bmp.Height - 1;
	for (int column = 0; column < bmp.Width; ++column)
	{
		lpPixelBufferLine = lpPixelBufferTempInitial + column * bmp.Height;
		for (int row = 0; row < bmp.Height; ++row)
		{
			unsigned long *lpPixelBuffer = lpPixelBufferInitial + bmp.ScanLineLength/4*row + column;
			_asm{
				mov edx, m_radius;
				imul edx, 2;
				add edx, 1;
				mov ecx, weight;
start_loop_v:
				mov ebx, m_radius;
				sub ebx, edx;
				add ebx, 1;
				add ebx, row;

				cmp ebx, lo;
				jge gt_than_low_v;
				mov ebx, lo;
gt_than_low_v:
				cmp ebx, hi;
				jle ls_than_high_v;
				mov ebx, hi;
ls_than_high_v:
				;��������, ebx�����ȷ����

					mov eax, lpPixelBufferLine;
				imul ebx, 4;
				add eax, ebx;

				pmovzxbd xmm0, [eax];
				cvtdq2ps xmm0, xmm0; ���α両��

				movd xmm1, [ecx];
				shufps xmm1, xmm1, 0x00;
				mulps xmm0, xmm1;
				addps xmm2, xmm0;

				add ecx, 4;
				dec edx;
				jnz start_loop_v;

				; ��Ҫ��xmm2��ÿһ��floatȡ���س�byte,ƴ��һ��long
					cvtps2dq xmm2, xmm2;
				packssdw xmm2, xmm2;
				mov esi, lpPixelBuffer;
				pextrw [esi], xmm2, 0;
				pextrw [esi+1], xmm2, 1;
				pextrw [esi+2], xmm2, 2;
				;pextrw [esi+3], xmm2, 3;
				mov [esi+3], 0xfe;��һλ��alpha
					emms;
			}
		}
	}
	free(lpPixelBufferTempInitial);
}

/*
FIR��˹ģ��������ά�ȵ���ģ����c++ʵ��;
����ˮƽ�����ģ��, ԭͼ������, ���д��ԭͼbuffer;
������ֱ�����ģ��, ˮƽģ������ԭͼ������, ���д��ԭͼbuffer
û�н���ת��, Ҳû�����⿪��ͼƬһ����С���ڴ�ռ������м���
���ʵ��ֻ��Ϊ����֤����ά�ȵ��ӵĸ�˹ģ��������ά��ͬʱ����ĸ�˹ģ����һ����, ��������ʹ��, ��Ϊ̫����!
*/
void OneDimentionRender(XL_BITMAP_HANDLE hBitmap, double m_sigma, int m_radius)
{
	assert(hBitmap);
	XLBitmapInfo bmp;
	XL_GetBitmapInfo(hBitmap, &bmp);

	assert(bmp.ColorType == XLGRAPHIC_CT_ARGB32);

	int diameter = m_radius * 2 + 1;
	float *weight;
	GaussianFunction(m_sigma, m_radius, &weight);

	unsigned long *lpPixelBufferLine;
	unsigned long *lpPixelBufferInitial = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, 0);

	for (int line = 0; line < bmp.Height; ++line)
	{
		lpPixelBufferLine = new unsigned long [bmp.Width];
		memcpy(lpPixelBufferLine, lpPixelBufferInitial + bmp.ScanLineLength/4*line, bmp.Width * 4);
		for (int col = 0; col < bmp.Width; ++col)
		{
			unsigned long *lpPixelBuffer = lpPixelBufferInitial + bmp.ScanLineLength/4*line + col;
			double redSum = 0;
			double greenSum = 0;
			double blueSum = 0;
			double alphaSum = 0;
			for (int j = -m_radius; j <= m_radius; j++)
			{
				unsigned long pixelBuffer;
				//Need read pixel @ line, col+j, if it's out of boundary, read boundary pixel
				if (col + j < 0)
				{
					pixelBuffer = lpPixelBufferLine[0];
				}
				else if (col + j >= bmp.Width)
				{
					pixelBuffer = lpPixelBufferLine[bmp.Width - 1];
				}
				else
				{
					pixelBuffer = lpPixelBufferLine[col + j];
				}
				unsigned int alpha = XLCOLOR_BGRA_A(pixelBuffer);
				unsigned int green = XLCOLOR_BGRA_G(pixelBuffer);
				unsigned int red = XLCOLOR_BGRA_R(pixelBuffer);
				unsigned int blue = XLCOLOR_BGRA_B(pixelBuffer);
				redSum += red * weight[j+m_radius];
				greenSum += green * weight[j+m_radius];
				blueSum += blue * weight[j+m_radius];
				alphaSum += alpha * weight[j+m_radius];
			}
			unsigned int alpha = alphaSum;
			unsigned int green = greenSum;
			unsigned int red = redSum;
			unsigned int blue = blueSum;
			*lpPixelBuffer = XLCOLOR_BGRA(blue, green, red, alpha);
		}
		delete []lpPixelBufferLine;
	}
	for (int column = 0; column < bmp.Width; ++column)
	{
		lpPixelBufferLine = new unsigned long [bmp.Height];
		for (int row = 0; row < m_radius; ++row)
		{
			lpPixelBufferLine[row] = *(lpPixelBufferInitial + bmp.ScanLineLength/4*row + column);
		}
		for (int row = 0; row < bmp.Height; ++row)
		{
			if (row + m_radius < bmp.Height)
			{
				lpPixelBufferLine[row+m_radius] = *(lpPixelBufferInitial + bmp.ScanLineLength/4*(row+m_radius)+column);
			}
			unsigned long *lpPixelBuffer = lpPixelBufferInitial + bmp.ScanLineLength/4*row + column;
			double redSum = 0;
			double greenSum = 0;
			double blueSum = 0;
			double alphaSum = 0;
			for (int j = -m_radius; j <= m_radius; j++)
			{
				unsigned long pixelBuffer;
				if (row + j < 0)
				{
					pixelBuffer = lpPixelBufferLine[0];
				}
				else if (row + j >= bmp.Height)
				{
					pixelBuffer = lpPixelBufferLine[bmp.Height-1];
				}
				else
				{
					pixelBuffer = lpPixelBufferLine[row+j];
				}
				unsigned int alpha = XLCOLOR_BGRA_A(pixelBuffer);
				unsigned int green = XLCOLOR_BGRA_G(pixelBuffer);
				unsigned int red = XLCOLOR_BGRA_R(pixelBuffer);
				unsigned int blue = XLCOLOR_BGRA_B(pixelBuffer);
				redSum += red * weight[j+m_radius];
				greenSum += green * weight[j+m_radius];
				blueSum += blue * weight[j+m_radius];
				alphaSum += alpha * weight[j+m_radius];
			}
			unsigned int alpha = alphaSum;
			unsigned int green = greenSum;
			unsigned int red = redSum;
			unsigned int blue = blueSum;
			*lpPixelBuffer = XLCOLOR_BGRA(blue, green, red, alpha);
		}
		delete []lpPixelBufferLine;
	}
}

/*
memcpy bmp.Height �ε�����bmp.Width * 4������
XL_GetBitmapBuffer 1��
*/
void TwoDimentionRender(XL_BITMAP_HANDLE hBitmap, double m_sigma, int m_radius)
{
	assert(hBitmap);
	XLBitmapInfo bmp;
	XL_GetBitmapInfo(hBitmap, &bmp);

	assert(bmp.ColorType == XLGRAPHIC_CT_ARGB32);

	int diameter = m_radius * 2 + 1;
	double *weight;
	GaussianFunction2(m_sigma, m_radius, &weight);
	unsigned long **lpPixelBufferLines = new unsigned long* [bmp.Height];
	unsigned long *lpPixelBufferInitial = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0,0);
	long lineWidth = bmp.ScanLineLength;
	// todo: ���λͼ�ǵ���洢��Ӧ����������? 

	for (int preloadLine = 0; preloadLine < m_radius; preloadLine++)
	{
		lpPixelBufferLines[preloadLine] = new unsigned long[bmp.Width];
		unsigned long *lpPixelBufferSourceLine = lpPixelBufferInitial + lineWidth/4 * preloadLine;
		// TODO, pixel buffer size should not be fixed 4 bytes
		memcpy(lpPixelBufferLines[preloadLine], lpPixelBufferSourceLine, bmp.Width * 4);
	}

	for (int line = 0; line < bmp.Height; ++line)
	{
		// bitmap��һ�е��ڴ��׵�ַ
		unsigned long *lpPixelBufferBmpLine = lpPixelBufferInitial + lineWidth/4 * line;
		// ��m_radius��֮ǰ��buffer�ͷŵ�, ��Ϊ���涼�ò�����
		if ( line >= m_radius + 1)
		{
			delete []lpPixelBufferLines[line - m_radius-1];
		}
		// ��ǰ����m_radius��֮���line, ��ΪҪ�õ�
		if (line + m_radius < bmp.Height)
		{
			lpPixelBufferLines[line + m_radius] = new unsigned long[bmp.Width];
			unsigned long *lpPixelBufferBmpLinePlusRadius = lpPixelBufferInitial + lineWidth/4 * (line + m_radius);
			memcpy(lpPixelBufferLines[line + m_radius], lpPixelBufferBmpLinePlusRadius, bmp.Width * 4);
		}

		for (int col = 0; col < bmp.Width; ++col)
		{
			unsigned long *lpPixelBuffer = lpPixelBufferBmpLine + col;
			double redSum = 0;
			double greenSum = 0;
			double blueSum = 0;
			double alphaSum = 0;
			for ( int i = -m_radius; i <= m_radius; i++)
			{
				for (int j = -m_radius; j <= m_radius; j++)
				{
					unsigned long pixelBuffer = 0;
					unsigned int adjustedLine, adjustedCol;
					if (line + i >= (int)bmp.Height)
					{
						adjustedLine = bmp.Height - 1;
					}
					else if (line + i < 0)
					{
						adjustedLine = 0;
					}
					else
					{
						adjustedLine = line + i;
					}
					if (col + j >= (int)bmp.Width)
					{
						adjustedCol = bmp.Width - 1;
					}
					else if (col + j < 0)
					{
						adjustedCol = 0;
					}
					else
					{
						adjustedCol = col + j;
					}
					pixelBuffer = lpPixelBufferLines[adjustedLine][adjustedCol];

					unsigned int alpha = XLCOLOR_BGRA_A(pixelBuffer);
					unsigned int green = XLCOLOR_BGRA_G(pixelBuffer);
					unsigned int red = XLCOLOR_BGRA_R(pixelBuffer);
					unsigned int blue = XLCOLOR_BGRA_B(pixelBuffer);
					redSum += red * weight[(i+m_radius)*diameter+(j+m_radius)];
					greenSum += green * weight[(i+m_radius)*diameter+(j+m_radius)];
					blueSum += blue * weight[(i+m_radius)*diameter+(j+m_radius)];
					alphaSum += alpha * weight[(i+m_radius)*diameter+(j+m_radius)];
				}
			}
			unsigned int alpha = alphaSum;
			unsigned int green = greenSum;
			unsigned int red = redSum;
			unsigned int blue = blueSum;
			*lpPixelBuffer = XLCOLOR_BGRA(blue, green, red, alpha);
		}
	}
	for (unsigned long bufferLine = bmp.Height - m_radius - 1; bufferLine < bmp.Height; bufferLine++)
	{
		delete []lpPixelBufferLines[bufferLine];
	}
	delete []lpPixelBufferLines;
}

void GaussianFunction(double sigma, int r, float ** results)
{
	*results =new float[r*2+1];
	double sum = 0;
	double factor = 1.0/sigma/sqrt(2*pi);
	for ( int i=0; i < r+1; i++)
	{
		(*results)[i] = exp(0- (i-r)*(i-r)/(2*sigma*sigma)) * factor;
		sum += (*results)[i];
	}
	for (int i = r+1; i < r*2+1; i++)
	{
		(*results)[i] = (*results)[r*2-i];
		sum += (*results)[i];
	}
	assert(sum>0);
	for (int i = 0; i < r*2+1; i++)
	{
		(*results)[i] /= sum;
	}
}

void GaussianFunction2(double sigma, int r, double **results)
{
	int D = r*2+1;
	*results = new double[D*D];
	double sum = 0;
	double factor = 1.0/2/pi/sigma/sigma;
	for ( int i = 0;i < r + 1; i++)
	{
		for (int j = 0; j < r+1; j++)
		{
			(*results)[i*D+j] = exp(0 - ((i-r)*(i-r) + (j-r)*(j-r))/(2*sigma*sigma)) * factor; 
			sum += (*results)[i*D+j];
		}
	}
	for (int i = r+1; i < D; i++)
	{
		for (int j= 0; j < r+1; j++)
		{
			(*results)[i*D+j] = (*results)[(r*2-i)*D+j];
			sum += (*results)[i*D+j];
		}
	}
	for (int i = 0; i < r+1; i++)
	{
		for (int j = r+1; j < D; j++)
		{
			(*results)[i*D+j] = (*results)[i*D+(r*2-j)];
			sum += (*results)[i*D+j];
		}
	}
	for (int i = r+1; i<D; i++)
	{
		for (int j = r+1; j< D; j++)
		{
			(*results)[i*D+j] = (*results)[(r*2-i)*D+(r*2-j)];
			sum += (*results)[i*D+j];
		}
	}
	double watch[49];
	for (int i = 0;i < D*D; i++)
	{
		(*results)[i] /= sum;
		watch[i] = (*results)[i];
	}
}
