/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2011              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   SafeWindow
*   Author      :   李亚星
*   Create      :   2011-10-24
*   LastChange  :   2011-10-24
*   History     :	
*
*   Description :   CWindowImpl和CDialogImpl的安全封装类，销毁时候不可使用delete来删除，需要调用对象
*					的SafeDelete方法来删除
********************************************************************/ 
#ifndef __SAFEWINDOW_H__
#define __SAFEWINDOW_H__

#include <atlbase.h>
#include <atlwin.h>

template<typename BaseWindow>
class SafeWindowWrapper
	: public BaseWindow
{
	typedef BaseWindow base_class;

public:

	BEGIN_MSG_MAP(SafeWindowWrapper)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		// 如果已经在删除中了，那么不再传递消息到父类，避免出错！
		if (m_bFinalDel)
		{
			return TRUE;
		}
		CHAIN_MSG_MAP(base_class)
	END_MSG_MAP()

	SafeWindowWrapper()
		:m_bFinalDel(false),
		m_bOnDestroy(false)
	{}

	void SafeDelete()
	{
		assert(!m_bFinalDel);

		if (base_class::IsWindow()) 
		{
			m_bFinalDel = true;

			if (!m_bOnDestroy)
			{
				End();
			}
		}
		else if (m_dwState & WINSTATE_DESTROYED)
		{
			// 窗口已经销毁，但是还没有到达最后一条消息
			m_bFinalDel = true;
		}
		else
		{
			m_bFinalDel = false;
			delete this;
		}
	}

protected:

	// 对象的删除只可以通过DeleteSelf来删除，不可以直接调用delete来删除！
	virtual ~SafeWindowWrapper()
	{
		
	}

private:

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;

		MarkOnDestroy();

		return 0;
	}

	void End()
	{
		// CDialogImplBaseT
		__if_exists(base_class::StartDialogProc)
		{
			base_class::EndDialog(0);
		}

		// CWindowImplBaseT
		__if_exists(base_class::StartWindowProc)
		{
			base_class::DestroyWindow();
		}
	}

	virtual void OnFinalMessage(HWND)
	{
		m_bOnDestroy = false;

		if (m_bFinalDel)
		{
			m_bFinalDel = false;
			delete this;
		}
	}

	void MarkOnDestroy()
	{
		assert(!m_bOnDestroy);
		m_bOnDestroy = true;
	}

private:

	bool    m_bFinalDel;        // 是否需要在onfinalmessage里面删除自己
	bool    m_bOnDestroy;       // 是否已经调用到Destroy或者EndDialog，防止重入
};


#endif //__SAFEWINDOW_H__