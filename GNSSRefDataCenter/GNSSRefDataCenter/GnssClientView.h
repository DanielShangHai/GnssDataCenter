#pragma once
#include "afxwin.h"


// CGnssClientView 视图

class CGnssClientView : public CListView
{
	DECLARE_DYNCREATE(CGnssClientView)

protected:
	CGnssClientView();           // 动态创建所使用的受保护的构造函数
	virtual ~CGnssClientView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	CFont m_fontItem;
	int m_nowCPLine;
	int m_nowCPcol;
public:
	virtual void OnInitialUpdate();
private:
	int m_curLine;
};


