/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   RotateObject
*   Author      :   李亚星
*   Create      :   2013-8-1 
*   LastChange  :   2013-8-1
*   History     :	
*
*   Description :   旋转对象，剪裁敏感，需要配合LayerObject使用
*
********************************************************************/ 
#ifndef __ROTATEOBJECT_H__
#define __ROTATEOBJECT_H__

#include "./RotateProvider.h"

#define EXTCLASSNAME_ROTATEOBJECT "RotateObject"

class RotateObject
	: public ExtLayoutObjMethodsImpl
{
public:
	RotateObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~RotateObject(void);

	void SetAngel(double angel);
	double GetAngel() const;

	bool SetStringX(const char* value);
	bool SetNumberX(int value);

	bool SetStringY(const char* value);
	bool SetNumberY(int value);

	POINT GetCenter() const;

	void SetRotateMode(RotateMode mode);
	RotateMode GetRotateMode() const;

private:

	// ExtLayoutObjMethodsImpl
	virtual void OnBind();
	virtual void OnPosChanged(const RECT* lpOldPos, const RECT* lpNewPos);
	virtual void OnPaintEx(XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect
		, unsigned char alpha, XLGraphicHint* lpHint);

private:

	void OnExpChange();

private:

	RECT m_objPos;

	PointExp m_centerPtExp;

	POINT m_centerPt;

	double m_angel;

	RotateMode m_mode;

	IRotateProvider* m_lpRotateProvider;
};




#endif // __ROTATEOBJECT_H__