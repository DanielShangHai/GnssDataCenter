#pragma once
#include "afxwin.h"


// CGnssRefStationView 视图

class CGnssRefStationView : public CListView
{
	DECLARE_DYNCREATE(CGnssRefStationView)

protected:
	CGnssRefStationView();           // 动态创建所使用的受保护的构造函数
	virtual ~CGnssRefStationView();

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
public:
	virtual void OnInitialUpdate();
private:
	int m_curLine;
public:
	void ReDrawList();
};


