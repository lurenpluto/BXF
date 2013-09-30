#include "stdafx.h"
#include "./DirtyRectObject.h"

DirtyRectObject::DirtyRectObject( XLUE_LAYOUTOBJ_HANDLE hObj )
:ExtLayoutObjMethodsImpl(hObj)
,m_genInterval(500)
,m_genTimer(0)
{
	m_timerManager.SetTimerProc(this, &DirtyRectObject::OnTimer);
}

DirtyRectObject::~DirtyRectObject(void)
{
	assert(m_genTimer == 0);
}

void DirtyRectObject::OnCreateHostWnd( XLUE_OBJTREE_HANDLE /*hTree*/, XLUE_HOSTWND_HANDLE /*hHostWnd*/, BOOL bCreate )
{
	if (bCreate)
	{
		assert(m_genTimer == 0);
		m_genTimer = m_timerManager.SetTimer(m_genInterval);
		assert(m_genTimer);
	}
	else
	{
		assert(m_genTimer);
		bool ret = m_timerManager.KillTimer(m_genTimer);
		assert(ret);
		(ret);
	}
}

void DirtyRectObject::OnTimer( unsigned int timerID )
{
	assert(timerID == m_genTimer);

	assert(IsValid());
	const RECT* lpPos = GetPos();
	if (RectHelper::IsRectEmpty(lpPos))
	{
		return;
	}

	long width = lpPos->right - lpPos->left;
	long height = lpPos->bottom - lpPos->top;

	RECT rcDirty;

	rcDirty.left = Random(0, width);
	rcDirty.top = Random(0, height);

	rcDirty.right = Random(rcDirty.left + 1, width + 1);
	rcDirty.bottom = Random(rcDirty.top + 1, height + 1);

	if (RectHelper::IntersectRect(&rcDirty, &rcDirty, lpPos))
	{
		PushDirtyRect(&rcDirty);
	}
}

long DirtyRectObject::Random( long minValue, long maxValue )
{
	assert(minValue < maxValue);

	::srand((unsigned int)::GetTickCount());

	return minValue + (unsigned long)::rand() % (maxValue - minValue);
}

void DirtyRectObject::SetGenInterval( unsigned int value )
{
	if (m_genInterval != value)
	{
		m_genInterval = value;

		if (m_genTimer != 0)
		{
			m_timerManager.SetIDTimer(m_genTimer, m_genInterval);
		}
	}
}

unsigned int DirtyRectObject::GetGenInterval() const
{
	return m_genInterval;
}