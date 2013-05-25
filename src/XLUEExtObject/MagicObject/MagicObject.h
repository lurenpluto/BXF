/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   MagicObject
*   Author      :   李亚星
*   Create      :   2013-5-20 0:18
*   LastChange  :   2013-5-20 0:18
*   History     :	
*
*   Description :   扩展对象之魔术对象~
*
********************************************************************/ 
#ifndef __MAGICOBJECT_H__
#define __MAGICOBJECT_H__

//#include "../../XLGraphicPlus/XLGraphicPlusAlgorithm.h"
//#pragma comment(lib, "XLGraphicPlus.lib")

#define EXTCLASSNAME_MAGICOBJECT "MagicObject"

class MagicObject
	: public ExtLayoutObjMethodsImpl
{
public:
	MagicObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~MagicObject(void);

	// ExternalObjMethods
	virtual void OnBind()
	{
		ExtLayoutObjMethodsImpl::OnBind();

		//
	}

	virtual void OnPaint(XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char alpha)
	{
		XL_BITMAP_HANDLE hBitmap = XL_ClipSubBindBitmap(hBitmapDest, lpDestClipRect);
		//XLGP_BlackAndWhite(hBitmap, 50, 0);
		XL_ReleaseBitmap(hBitmap);
	}
private:

	BitmapResHolder m_bkn;
};

#endif // __MAGICOBJECT_H__