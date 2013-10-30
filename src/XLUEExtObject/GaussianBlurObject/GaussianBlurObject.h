/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#ifndef __GAUSSIANBLUROBJECT_H__
#define __GAUSSIANBLUROBJECT_H__

#include "./GaussianBlurDelegate.h";

class GaussianBlurObject
	: public ExtLayoutObjMethodsImpl
{
public:
	GaussianBlurObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~GaussianBlurObject(void);

public:

	enum Type 
	{
		UnDefined = 0,
		OneDimentionMMX = 1, 
		DirecheIIRSSE = 2, 
		Default = 3, 
		ValidType = 4
	};

	// ExtLayoutObjMethodsImpl virtual funtions

	// 该对象是剪裁敏感的，所以需要配合LayerObject+clipsens使用
	virtual void OnPaint(XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char alpha);

	void SetSigma(const float &sigma);
	float GetSigma() const;

	void SetRadius(const int &radius);
	int GetRadius() const;

	void SetGaussianType(const char *type) ;
	const char* GetGaussianType() const;

private:
	float m_sigma;
	int m_radius;
	Type m_type;
};

#endif // __GAUSSIANBLUROBJECT_H__