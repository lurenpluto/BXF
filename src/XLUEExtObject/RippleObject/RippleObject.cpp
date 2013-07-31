/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./RippleObject.h"

RippleObject::RippleObject(XLUE_LAYOUTOBJ_HANDLE hObj)
:ExtLayoutObjMethodsImpl(hObj),
m_updateInterval(50),
m_randomDropInterval(300),
m_updateTimerID(0),
m_randomDropTimerID(0),
m_dropDensity(3),
m_randomdrop(true),
m_fineMode(true),
m_mouseDrop(true),
m_waterDensity(2)
{
	m_timerManager.SetTimerProc(this, &RippleObject::OnTimer);
}

RippleObject::~RippleObject(void)
{
	assert(m_updateTimerID == 0);
	assert(m_randomDropTimerID == 0);
	KillRandomDropTimer();
	KillUpdateTimer();
}

void RippleObject::OnTimer( unsigned int timerID )
{
	if (timerID == m_updateTimerID)
	{
		UpdateAllRipple();
	}
	else if (timerID == m_randomDropTimerID)
	{
		GenerateRandomDrops();
	}
	else
	{
		assert(false);
	}
}

void RippleObject::StartUpdateTimer()
{
	if (m_updateTimerID == 0)
	{
		m_updateTimerID = m_timerManager.SetTimer(m_updateInterval);
		assert(m_updateTimerID);
	}
}

void RippleObject::KillUpdateTimer()
{
	if (m_updateTimerID != 0)
	{
		m_timerManager.KillTimer(m_updateTimerID);
		m_updateTimerID = NULL;
	}
}

void RippleObject::StartRandomDropTimer()
{
	if (m_randomDropTimerID == 0)
	{
		m_randomDropTimerID = m_timerManager.SetTimer(m_randomDropInterval);
		assert(m_randomDropTimerID);
	}
}

void RippleObject::KillRandomDropTimer()
{
	if (m_randomDropTimerID != 0)
	{
		m_timerManager.KillTimer(m_randomDropTimerID);
		m_randomDropTimerID = NULL;
	}
}

void RippleObject::OnInitControl()
{
	if (m_randomdrop)
	{
		StartRandomDropTimer();
	}
}

void RippleObject::OnDestroy()
{
	KillUpdateTimer();
	KillRandomDropTimer();
}

static unsigned long long GetCycleCount()
{   
	__asm  _emit   0x0F   
	__asm  _emit   0x31   
}   

void RippleObject::GenerateRandomDrops()
{
	if (m_dropDensity == 0 || m_dropDensity >= 0xFFFF)
	{
		return;
	}

	unsigned long odds = m_randomDropInterval * m_dropDensity / 5;
	bool update = false;

	for(;;)
	{
		if (odds >= 1000)
		{
			odds -= 1000;
		}
		else
		{
			::srand((unsigned int)GetCycleCount());  
			if (((unsigned long)::rand() % 1000) > odds)
			{
				break;
			}
		}
		
		::srand((unsigned int)GetCycleCount());  
		short height = 50 + (::rand() % 200);
		
		::srand((unsigned int)GetCycleCount());  
		short radius = 3 + (::rand() % 10);

		RippleHolder holder;
		if (GenerateRipple(holder, radius, height))
		{
			m_rippleItems.push_back(holder);

			update = true;
		}
	}

	if (update && !m_rippleItems.empty())
	{
		StartUpdateTimer();
	}
}

void RippleObject::UpdateAllRipple()
{
	vtRippleItems left;
	vtRippleItems::iterator cp, end = m_rippleItems.end();
	for (cp = m_rippleItems.begin(); cp != end; ++cp)
	{
		RippleItem* lpItem = (*cp).lpRippleItem;
		assert(lpItem);

		if (lpItem->UpdateFrame())
		{
			left.push_back(*cp);
		}
		else
		{
			delete lpItem;
		}

		PushDirtyRect(&((*cp).pos));
	}

	m_rippleItems.swap(left);

	if (m_rippleItems.empty())
	{
		KillUpdateTimer();
	}
}

void RippleObject::OnPaint( XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char /*alpha*/ )
{
	// 水波对象不使用自身的alpha
	vtRippleItems::iterator cp, end = m_rippleItems.end();
	for (cp = m_rippleItems.begin(); cp != end; ++cp)
	{
		RippleItem* lpItem = (*cp).lpRippleItem;
		const RECT& pos = (*cp).pos;
		assert(lpItem);

		RECT rcUpdate;
		if (RectHelper::IntersectRect(&rcUpdate, lpSrcClipRect, &pos))
		{
			RECT rcDest = *lpDestClipRect;
			rcDest.left = rcDest.left + (rcUpdate.left - lpSrcClipRect->left);
			rcDest.top = rcDest.top + (rcUpdate.top - lpSrcClipRect->top);
			rcDest.right = rcDest.left + (rcUpdate.right - rcUpdate.left);
			rcDest.bottom = rcDest.top + (rcUpdate.bottom - rcUpdate.top);

			RectHelper::OffsetRect(&rcUpdate, -pos.left, -pos.top);

			lpItem->Draw(hBitmapDest, &rcDest, &rcUpdate);
		}
	}
}

long RippleObject::PostInputFilter( unsigned long actionType, unsigned long wParam, unsigned long lParam, BOOL* lpHandled )
{
	assert(lpHandled);

	POINT ptNow;
	ptNow.x = ((long)(short)LOWORD(lParam));
	ptNow.y = ((long)(short)HIWORD(lParam));

	const RECT* lpPos = GetAbsPos();
	assert(lpPos);
	ptNow.x -= lpPos->left;
	ptNow.y -= lpPos->top;

	bool update = true;
	if (actionType == XLUE_ACTION_LMOUSE_DOWN
		|| actionType == XLUE_ACTION_RMOUSE_DOWN)
	{
		RippleHolder holder;
		if (GenerateRipple(holder, 10, 300, ptNow.x, ptNow.y))
		{
			m_rippleItems.push_back(holder);
		}
	}
	else if (actionType == XLUE_ACTION_MOUSE_MOVE)
	{
		RippleHolder holder;
		short radius, height;
		if ((wParam & XLUE_MK_LBUTTON) || (wParam & XLUE_MK_RBUTTON))
		{
			radius = 8;
			height = 150;
		}
		else
		{
			radius = 5;
			height = 15;
		}

		if (GenerateRipple(holder, radius, height, ptNow.x, ptNow.y))
		{
			m_rippleItems.push_back(holder);
		}
	}
	else
	{
		update = false;
	}

	if (update && !m_rippleItems.empty())
	{
		*lpHandled = TRUE;
		StartUpdateTimer();
	}

	return 0;
}

bool RippleObject::GenerateRipple( RippleHolder& holder, short radius, short height, long x /*= LONG_MAX*/, long y /*= LONG_MAX*/)
{
	const RECT* lpPos = GetAbsPos();
	assert(lpPos);
	if (lpPos == NULL)
	{
		return false;
	}

	RippleItem* lpNewItem = RippleItemGenerator::Generate(radius, height, m_waterDensity, m_fineMode);
	
	long left = 0;
	if (x == LONG_MAX)
	{
		::srand((unsigned int)GetCycleCount());  
		left = ::rand() % (lpPos->right - lpPos->left);
	}
	else
	{
		left = x - (long)lpNewItem->GetWidth() / 2;
	}

	long top = 0;
	if (y == LONG_MAX)
	{
		::srand((unsigned int)GetCycleCount());  
		top = ::rand() % (lpPos->bottom - lpPos->top);
	}
	else
	{
		top = y - (long)lpNewItem->GetWidth() / 2;
	}

	holder.lpRippleItem  =lpNewItem;
	holder.pos.left = left;
	holder.pos.top = top;
	holder.pos.right = holder.pos.left + (long)lpNewItem->GetWidth();
	holder.pos.bottom = holder.pos.top + (long)lpNewItem->GetWidth();

	return true;
}

void RippleObject::SetRandomDrop( bool enable )
{
	if (m_randomdrop != enable)
	{
		m_randomdrop = enable;

		if (m_randomdrop)
		{
			StartRandomDropTimer();
		}
		else
		{
			KillRandomDropTimer();
		}
	}
}

bool RippleObject::GetRandomDrop()
{
	return m_randomdrop;
}

void RippleObject::SetUpdateInterval( unsigned long interval )
{
	// 最小更新时间间隔不可小于30ms
	if (interval < 30)
	{
		interval = 30;
	}

	if (m_updateInterval != interval)
	{
		m_updateInterval = interval;

		KillUpdateTimer();
		StartUpdateTimer();
	}
}

unsigned long RippleObject::GetUpdateInterval()
{
	return m_updateInterval;
}

bool RippleObject::CanHandleInput()
{
	if (m_mouseDrop)
	{
		return true;
	}

	return false;
}

void RippleObject::SetMouseDrop( bool enable )
{
	m_mouseDrop = enable;
}

bool RippleObject::GetMouseDrop()
{
	return m_mouseDrop;
}

void RippleObject::ClearAllDrops()
{
	if (m_rippleItems.empty())
	{
		return;
	}

	vtRippleItems::iterator cp, end = m_rippleItems.end();
	for (cp = m_rippleItems.begin(); cp != end; ++cp)
	{
		RippleItem* lpItem = (*cp).lpRippleItem;
		assert(lpItem);

		delete lpItem;
	}

	PushDirtyRect(NULL);

	KillUpdateTimer();
}

void RippleObject::SetDropDensity( unsigned long density )
{
	m_dropDensity = density;
}

unsigned long RippleObject::GetDropDensity()
{
	return m_dropDensity;
}

void RippleObject::SetWaterDensity( unsigned long density )
{
	// 衰减因子不可小于1，否则会导致无法扩散
	// 也不可大于8，否则会导致无法衰减而成为"永动机"
	if (density < 1)
	{
		density = 1;
	}
	else if (density > 8)
	{
		density = 8;
	}

	m_waterDensity = (char)density;
}

unsigned long RippleObject::GetWaterDensity()
{
	return m_waterDensity;
}