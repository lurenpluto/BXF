/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   MirrorObject
*   Author      :   李亚星
*   Create      :   2013-5-26 11:35
*   LastChange  :   2013-5-26 11:35
*   History     :	
*
*   Description :   镜像对象，可以对一个对象或者一组对象的渲染结果进行镜像处理
*
********************************************************************/ 
#ifndef __MIRROROBJECT_H__
#define __MIRROROBJECT_H__


class MirrorObject
	: public ExtLayoutObjMethodsImpl
{
public:

	enum MirrorType
	{
		MirrorType_none = 0,
		MirrorType_hor = 1,
		MirrorType_ver = 2,
		MirrorType_both = 3,
	};

public:

	MirrorObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~MirrorObject(void);

	void SetMirrorType(MirrorType type);
	MirrorType GetMirrorType() const;

public:

	// ExtLayoutObjMethodsImpl virtual funtions

	// 该对象是剪裁敏感的，所以需要配合LayerObject+clipsens使用
	virtual void OnPaint(XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char alpha);

private:

	void HorizontalMirror(XL_BITMAP_HANDLE hBitmap) const;
	void VerticalMirror(XL_BITMAP_HANDLE hBitmap) const;
	void BothMirror(XL_BITMAP_HANDLE hBitmap) const;

private:

	MirrorType m_mirrorType;
};

#endif // __MIRROROBJECT_H__