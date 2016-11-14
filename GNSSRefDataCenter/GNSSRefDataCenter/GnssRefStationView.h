#pragma once
#include "afxwin.h"


// CGnssRefStationView ��ͼ

class CGnssRefStationView : public CListView
{
	DECLARE_DYNCREATE(CGnssRefStationView)

protected:
	CGnssRefStationView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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


