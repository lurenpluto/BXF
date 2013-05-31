/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   RippleObject
*   Author      :   李亚星
*   Create      :   2013-5-28
*   LastChange  :   2013-5-28
*   History     :	
*
*   Description :   水波动画对象，属后置渲染对象，剪裁敏感，如果该对象不配合敏感LayerObject
*					使用，可能会在某些情况下水波中出现切线效果
*					目前使用的算法是基于每个水滴一个RippleItem的方法，在对象上有较少水滴时候效率较高，
*					但如果界面上存在较多水滴，并且水密度较小，那么效率会很低，以后会引入整体水波处理机制
********************************************************************/ 
#ifndef __RIPPLEOBJECT_H__
#define __RIPPLEOBJECT_H__

#include "./RippleItem.h"
#include <vector>

class RippleObject
	: public ExtLayoutObjMethodsImpl
{
private:

	struct RippleHolder
	{
		RippleItem* lpRippleItem;
		RECT pos;
	};

public:
	RippleObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~RippleObject(void);

	void SetMouseDrop(bool enable);
	bool GetMouseDrop();

	void SetRandomDrop(bool enable);
	bool GetRandomDrop();

	void SetDropDensity(unsigned long density);
	unsigned long GetDropDensity();

	void SetUpdateInterval(unsigned long interval);
	unsigned long GetUpdateInterval();

	void SetWaterDensity(unsigned long density);
	unsigned long GetWaterDensity();

	void ClearAllDrops();

private:

	// LayoutObject virtual funcs
	virtual void OnInitControl();
	virtual void OnDestroy();

	virtual void OnPaint(XL_BITMAP_HANDLE /*hBitmapDest*/, const RECT* /*lpDestClipRect*/, const RECT* /*lpSrcClipRect*/, unsigned char /*alpha*/);

	virtual bool CanHandleInput();
	virtual long PostInputFilter(unsigned long actionType, unsigned long /*wParam*/, unsigned long /*lParam*/, BOOL* lpHandled);

private:

	// Timer
	void OnTimer(unsigned int timerID);

private:

	void StartUpdateTimer();
	void KillUpdateTimer();

	void StartRandomDropTimer();
	void KillRandomDropTimer();

	void GenerateRandomDrops();
	void UpdateAllRipple();

	bool GenerateRipple(RippleHolder& holder, short radius, short height, long x = LONG_MAX, long y = LONG_MAX);

private:

	// 是否跟踪鼠标消息来产生水滴
	bool m_mouseDrop;

	// 是否生成随机水滴
	bool m_randomdrop;

	// 随机水滴时间间隔，默认为1s
	unsigned long m_randomDropInterval;

	// 水波帧间隔，默认为50ms，最小为30ms
	unsigned long m_updateInterval;

	// 随机水滴驱动timer
	unsigned long m_randomDropTimerID;

	// 水波帧间隔驱动timer
	unsigned long m_updateTimerID;

	// 随机水滴密度，为每5s时间间隔内，随机产生的水滴个数
	unsigned long m_dropDensity;

	// 水波柔和模式
	bool m_fineMode;

	// 衰减因子，为方便理解定义为水密度
	char m_waterDensity;

	typedef MemberTimerManagerWrapperT<RippleObject> RippleMemberTimerManager;
	RippleMemberTimerManager m_timerManager;

	// 当前的所有“水滴”
	typedef std::vector<RippleHolder> vtRippleItems;
	vtRippleItems m_rippleItems;
};

#endif // __RIPPLEOBJECT_H__