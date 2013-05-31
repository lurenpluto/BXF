#include "stdafx.h"
#include "./RippleItem.h"
#include <math.h>

RippleItem::RippleItem(size_t width, short radius, short height, char dampingRatio, bool fineMode)
:m_width(width),
m_radius(radius),
m_height(height),
m_lpCurrentFrame(NULL),
m_fineMode(fineMode),
m_dampingRatio(dampingRatio),
m_fadeHeight(5)
{
	assert(height > 0);
	assert(m_radius > 0);
	assert((size_t)m_radius * 2 < width - 1);
	assert(m_dampingRatio > 0);

	m_lpFrameBuffer1 = (short*)::malloc(m_width * m_width * sizeof(short));
	m_lpFrameBuffer2 = (short*)::malloc(m_width * m_width * sizeof(short));

	::memset(m_lpFrameBuffer1, 0, m_width * m_width * sizeof(short));
	::memset(m_lpFrameBuffer2, 0, m_width * m_width * sizeof(short));

	Init();
}

RippleItem::~RippleItem(void)
{
	assert(m_lpFrameBuffer1);
	::free(m_lpFrameBuffer1);
	m_lpFrameBuffer1 = NULL;

	assert(m_lpFrameBuffer2);
	::free(m_lpFrameBuffer2);
	m_lpFrameBuffer2 = NULL;
}

void RippleItem::Init()
{
	assert(m_lpCurrentFrame == NULL);
	assert(m_lpFrameBuffer1);
	assert(m_lpFrameBuffer2);

	m_lpCurrentFrame = m_lpFrameBuffer1;
	
	// 生成第一帧的水波数据
	const size_t x = m_width / 2, y = x;
	const size_t rp = m_radius * m_radius;
	short* lpFramePointer = m_lpCurrentFrame;

	for (size_t line = y - m_radius; line < y + m_radius; ++line)
	{
		lpFramePointer = m_lpCurrentFrame + line * m_width + (x - m_radius);
		const size_t lp = (line - y) * (line - y);
		
		for (size_t col = x - m_radius; col < x + m_radius; ++col)
		{
			const size_t cp = (col - x) * (col - x);
			if (lp + cp < rp)
			{
				*lpFramePointer = m_height;
			}

			++lpFramePointer;
		}
	}
}

void RippleItem::Update(size_t& leftPoints)
{
	// 跳到下一帧缓冲
	short* lpOldFrame;
	if (m_lpCurrentFrame == m_lpFrameBuffer1)
	{
		m_lpCurrentFrame = m_lpFrameBuffer2;
		lpOldFrame = m_lpFrameBuffer1;
	}
	else
	{
		m_lpCurrentFrame = m_lpFrameBuffer1;
		lpOldFrame = m_lpFrameBuffer2;
	}

	// 选择不同模式下的水波演算算法
	if (m_fineMode)
	{
		UpdateInFineMode(lpOldFrame, m_lpCurrentFrame, leftPoints);
	}
	else
	{
		UpdateInNormalMode(lpOldFrame, m_lpCurrentFrame, leftPoints);
	}
}

void RippleItem::UpdateInFineMode( const short *lpOldFrameBuffer, short* lpNewFrameBuffer, size_t& leftPoints )
{
	assert(lpOldFrameBuffer);
	assert(lpNewFrameBuffer);

	const short *lpPreLineBuffer = lpOldFrameBuffer;
	const short *lpCurrentLineBuffer = lpOldFrameBuffer + m_width;
	const short *lpNextLineBuffer = lpCurrentLineBuffer + m_width;

	short *lpCurrentNewLineBuffer = lpNewFrameBuffer + m_width;

	// 更新整个作用域，避开四边
	for (size_t line = 1; line < m_width - 1; ++line)
	{
		for (size_t col = 1; col < m_width - 1; ++col)
		{
			int newHeight = ((lpPreLineBuffer[col - 1] + lpPreLineBuffer[col] + lpPreLineBuffer[col + 1]
				+ lpCurrentLineBuffer[col - 1] + lpCurrentLineBuffer[col + 1] 
				+ lpNextLineBuffer[col - 1] + lpNextLineBuffer[col] + lpNextLineBuffer[col + 1]) >> 2) - lpCurrentNewLineBuffer[col];

			newHeight = newHeight - (newHeight >> m_dampingRatio);

			if (newHeight != 0)
			{
				++leftPoints;
			}

			lpCurrentNewLineBuffer[col] = (short)newHeight;
		}

		lpCurrentNewLineBuffer += m_width;
		lpPreLineBuffer = lpCurrentLineBuffer;
		lpCurrentLineBuffer = lpNextLineBuffer;
		lpNextLineBuffer += m_width;
	}
}

void RippleItem::UpdateInNormalMode( const short *lpOldFrameBuffer, short* lpNewFrameBuffer, size_t& leftPoints )
{
	assert(lpOldFrameBuffer);
	assert(lpNewFrameBuffer);

	const short *lpPreLineBuffer = lpOldFrameBuffer;
	const short *lpCurrentLineBuffer = lpOldFrameBuffer + m_width;
	const short *lpNextLineBuffer = lpCurrentLineBuffer + m_width;

	short *lpCurrentNewLineBuffer = lpNewFrameBuffer + m_width;

	// 更新整个作用域，避开四边
	for (size_t line = 1; line < m_width - 1; ++line)
	{
		for (size_t col = 1; col < m_width - 1; ++col)
		{
			int newHeight = ((lpPreLineBuffer[col] + lpCurrentLineBuffer[col - 1] 
				+ lpCurrentLineBuffer[col + 1] + lpNextLineBuffer[col]) >> 1) - lpCurrentNewLineBuffer[col];
			
			newHeight = newHeight - (newHeight >> m_dampingRatio);

			if (newHeight != 0)
			{
				++leftPoints;
			}

			lpCurrentNewLineBuffer[col] = (short)newHeight;
		}

		lpCurrentNewLineBuffer += m_width;
		lpPreLineBuffer = lpCurrentLineBuffer;
		lpCurrentLineBuffer = lpNextLineBuffer;
		lpNextLineBuffer += m_width;
	}
}

void RippleItem::Draw( XL_BITMAP_HANDLE hBitmap, const RECT* lpDestRect, const RECT* lpSrcRect )
{
	assert(hBitmap);
	assert(lpDestRect);
	assert(lpSrcRect);
	assert(lpDestRect->right- lpDestRect->left == lpSrcRect->right - lpSrcRect->left);
	assert(lpDestRect->bottom- lpDestRect->top == lpSrcRect->bottom - lpSrcRect->top);
	assert(lpSrcRect->right <= (long)m_width);
	assert(lpSrcRect->bottom <= (long)m_width);
	assert(lpSrcRect->left >= 0);
	assert(lpSrcRect->top >= 0);

	// 当前帧作用于目标位图，避开四边
	assert(m_lpCurrentFrame);
	RECT realSrcRect = *lpSrcRect;
	if (realSrcRect.left < 1)
	{
		realSrcRect.left = 1;
	}
	if (realSrcRect.right >= (long)m_width)
	{
		realSrcRect.right = (long)m_width - 1;
	}
	if (realSrcRect.top < 1)
	{
		realSrcRect.top = 1;
	}
	if (realSrcRect.bottom >= (long)m_width)
	{
		realSrcRect.bottom = (long)m_width - 1;
	}

	assert(m_lpCurrentFrame);
	short* lpFramePointer = m_lpCurrentFrame + realSrcRect.top * m_width;
	unsigned long* lpDestBuffer = (unsigned long*)XL_GetBitmapBuffer(hBitmap, lpDestRect->left, lpDestRect->top);
	
	XLBitmapInfo bmp;
	XL_GetBitmapInfo(hBitmap, &bmp);

	const long scanlineWidth = bmp.ScanLineLength / 4;
	unsigned long* lpDestPointer = lpDestBuffer + (realSrcRect.top - lpSrcRect->top) * scanlineWidth;

	for (long line = realSrcRect.top; line < realSrcRect.bottom; ++line)
	{
		for (long col = realSrcRect.left; col < realSrcRect.right; ++col)
		{
			// 计算水平和垂直折射因子，这里可有多种算法，这里暂时使用临近两个点的算法
			// 水波高度是0-100标准区间
			short x = lpFramePointer[col] - lpFramePointer[col + 1];
			if (x != 0)
			{
				const short y = lpFramePointer[col] - lpFramePointer[col + m_width];

				const long destLine = line + y;
				const long destCol = col + x;

				if (destCol >= lpSrcRect->left && destCol < lpSrcRect->right 
					&& destLine >= lpSrcRect->top && destLine < lpSrcRect->bottom)
				{
					const unsigned long* lpDestPixel = lpDestBuffer + (destLine - lpSrcRect->top) * scanlineWidth + (destCol - lpSrcRect->left);
					const unsigned long pixel = *lpDestPixel;
					int r = XLCOLOR_BGRA_R(pixel);
					int g = XLCOLOR_BGRA_G(pixel);
					int b = XLCOLOR_BGRA_B(pixel);
					int a = XLCOLOR_BGRA_A(pixel);

					// 放大水波造成的折射效果
					x = x << 2;

					if (x > 0)
					{
						r = max(r - x, 0);
						g = max(g - x, 0);
						b = max(b - x, 0);
					}
					else
					{
						r = min(r - x, 255);
						g = min(g - x, 255);
						b = min(b - x, 255);
					}

					lpDestPointer[col - lpSrcRect->left] = XLCOLOR_BGRA(b, g, r, a);
				}
			}
		}

		lpFramePointer += m_width;
		lpDestPointer += scanlineWidth;
	}
}

bool RippleItem::UpdateFrame()
{
	size_t leftPoints = 0;
	Update(leftPoints);

	bool ret = true;
	// 如果剩余量小于一定数量，那么认为该水波消失了，设定0，让水波消失的更彻底
	if (leftPoints == 0)
	{
		ret = false;
	}

	return ret;
}

RippleItem* RippleItemGenerator::Generate( short radius, short height, char dampingRatio, bool fineMode )
{
	// 估算水波可能扩大到的最大范围
	// 衰减距离
	size_t dampingSize = (size_t)(pow(2.0, dampingRatio) * 3 / 2);
	// 折射距离
	size_t refractSize = (height >> (dampingRatio - 1));
	size_t width = (radius * 2) + (dampingSize * 2) + (refractSize * 2) + 4;

	RippleItem* lpNewItem = new RippleItem(width, radius, height, dampingRatio, fineMode);

	return lpNewItem;
}