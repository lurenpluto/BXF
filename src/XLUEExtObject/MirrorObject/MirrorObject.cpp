#include "stdafx.h"
#include "./MirrorObject.h"

MirrorObject::MirrorObject( XLUE_LAYOUTOBJ_HANDLE hObj )
:ExtLayoutObjMethodsImpl(hObj),
m_mirrorType(MirrorType_none)
{

}

MirrorObject::~MirrorObject(void)
{
}

void MirrorObject::OnPaint( XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char /*alpha*/ )
{
	assert(lpSrcClipRect);
	assert(RectHelper::EqualRect(lpSrcClipRect, GetPos()));

	if (m_mirrorType == MirrorType_none)
	{
		return;
	}

	XL_BITMAP_HANDLE hClipBitmap = XL_ClipSubBindBitmap(hBitmapDest, lpDestClipRect);
	assert(hClipBitmap);

	if (m_mirrorType == MirrorType_hor)
	{
		HorizontalMirror(hClipBitmap);
	}
	else if (m_mirrorType == MirrorType_ver)
	{
		VerticalMirror(hClipBitmap);
	}
	else if (m_mirrorType == MirrorType_both)
	{
		BothMirror(hClipBitmap);
	}
	else
	{
		assert(false);
	}

	XL_ReleaseBitmap(hClipBitmap);
}

void MirrorObject::HorizontalMirror( XL_BITMAP_HANDLE hBitmap ) const
{
	assert(hBitmap);
	XLBitmapInfo bmp;
	XL_GetBitmapInfo(hBitmap, &bmp);

	assert(bmp.ColorType == XLGRAPHIC_CT_ARGB32);

	for (unsigned long line = 0; line < bmp.Height; ++line)
	{
		unsigned long* lpLeftBuffer = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, line);
		unsigned long* lpRightBuffer = (unsigned long*)XL_GetBitmapBuffer(hBitmap, bmp.Width - 1, line);

		while(lpLeftBuffer < lpRightBuffer)
		{
			unsigned long tmp = *lpLeftBuffer;
			*lpLeftBuffer = *lpRightBuffer;
			*lpRightBuffer = tmp;

			++lpLeftBuffer;
			--lpRightBuffer;
		}
	}
}

void MirrorObject::VerticalMirror( XL_BITMAP_HANDLE hBitmap ) const
{
	assert(hBitmap);
	XLBitmapInfo bmp;
	XL_GetBitmapInfo(hBitmap, &bmp);

	assert(bmp.ColorType == XLGRAPHIC_CT_ARGB32);

	size_t lineBytes = bmp.Width * 4;
	unsigned long *lpTmpLine = (unsigned long*)::malloc(lineBytes);
	assert(lpTmpLine);
	if (lpTmpLine == NULL)
	{
		return;
	}

	for (unsigned long line = 0; line < bmp.Height / 2; ++line)
	{
		unsigned long* lpTopBuffer = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, line);
		unsigned long* lpBottomBuffer = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, bmp.Height - line - 1);

		if (lpTopBuffer < lpBottomBuffer)
		{
			::memcpy(lpTmpLine, lpTopBuffer, lineBytes);
			::memcpy(lpTopBuffer, lpBottomBuffer, lineBytes);
			::memcpy(lpBottomBuffer, lpTmpLine, lineBytes);
		}	
	}

	::free(lpTmpLine);
}

void MirrorObject::BothMirror( XL_BITMAP_HANDLE hBitmap ) const
{
	assert(hBitmap);
	XLBitmapInfo bmp;
	XL_GetBitmapInfo(hBitmap, &bmp);

	assert(bmp.ColorType == XLGRAPHIC_CT_ARGB32);

	for (unsigned long line = 0; line < bmp.Height / 2; ++line)
	{
		unsigned long* lpTopLeftBuffer = (unsigned long*)XL_GetBitmapBuffer(hBitmap, 0, line);
		unsigned long* lpBottomRightBuffer = (unsigned long*)XL_GetBitmapBuffer(hBitmap, bmp.Width - 1, bmp.Height - line - 1);

		for (unsigned long col = 0; col < bmp.Width; ++col)
		{
			unsigned long tmp = *lpTopLeftBuffer;
			*lpTopLeftBuffer = *lpBottomRightBuffer;
			*lpBottomRightBuffer = tmp;

			++lpTopLeftBuffer;
			--lpBottomRightBuffer;
		}
	}
}

void MirrorObject::SetMirrorType( MirrorType type )
{
	if (m_mirrorType == type)
	{
		return;
	}

	m_mirrorType = type;

	PushDirtyRect(NULL);
}

MirrorObject::MirrorType MirrorObject::GetMirrorType() const
{
	return m_mirrorType;
}