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
*   FileName    :   DirtyRectObject
*   Author      :   李亚星
*   Create      :   2013-9-27 
*   LastChange  :   2013-9-27
*   History     :	
*
*   Description :   脏矩形对象，可以在指定区域内随机产生脏矩形，主要用以测试
*
********************************************************************/ 
#ifndef __DIRTYRECTOBJECT_H__
#define __DIRTYRECTOBJECT_H__

#define EXTCLASSNAME_DIRTYRECTOBJECT "DirtyRectObject"

class DirtyRectObject
	: public ExtLayoutObjMethodsImpl
{
private:

	typedef MemberTimerManagerWrapperT<DirtyRectObject> DirtyRectObjectTimer;

public:
	DirtyRectObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~DirtyRectObject(void);

	void SetGenInterval(unsigned int value);
	unsigned int GetGenInterval() const;

private:

	// ExtLayoutObjMethodsImpl
	virtual void OnCreateHostWnd(XLUE_OBJTREE_HANDLE /*hTree*/, XLUE_HOSTWND_HANDLE /*hHostWnd*/, BOOL bCreate);

	void OnTimer(unsigned int timerID);

	// 产生[minValue, maxValue)区间的随机数
	static long Random(long minValue, long maxValue);

private:

	unsigned int m_genInterval;
	unsigned int m_genTimer;

	DirtyRectObjectTimer m_timerManager;
};

#endif // __DIRTYRECTOBJECT_H__