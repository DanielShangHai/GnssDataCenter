#pragma once
#include "afxwin.h"


// CGnssClientView ��ͼ

class CGnssClientView : public CListView
{
	DECLARE_DYNCREATE(CGnssClientView)

protected:
	CGnssClientView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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


