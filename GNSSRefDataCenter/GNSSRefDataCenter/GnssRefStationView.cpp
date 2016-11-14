// GnssRefStationView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GNSSRefDataCenter.h"
#include "GnssRefStationView.h"
#include "MainFrm.h"
#include "GNSSRefDataCenter.h"

// CGnssRefStationView



typedef struct tagREPORT_ITEM
{
	LPCTSTR name;
	int     width;
} REPORT_ITEM, *LPREPORT_ITEM;

const REPORT_ITEM s_reportItems[] =
{
	{ _T("�ο�վ�ն�"), 100 },
	{ _T("����Դ�˿ں�"), 130 },
	{ _T("�ͻ�����˿ں�"), 140 },
	{ _T("����Դ����"), 100 },
	{ _T("���߿ͻ���"), 110 },
	{ _T("�ϴ�����(�ֽ�)"), 140 },
	{ _T("�·�����(�ֽ�)"), 140 },
	{ _T("״̬"), 50 }
};

const TCHAR lpszSTATUS_UNCONNECT[] = _T("������δ����");
const TCHAR lpszSTATUS_CONNECT[] = _T("������������");

#define INDEX_REF_STATION_NAME         0
#define INDEX_DATASOURCE_PORT          1
#define INDEX_CLIENT_IN_PORT           2
#define INDEX_DATASOURCE_TYPE          3
#define INDEX_ONLINE_CLIENT            4
#define INDEX_UPLOAD_FLOW              5
#define INDEX_DOWNLOAD_FLOW            6
#define INDEX_STATUS                   7




IMPLEMENT_DYNCREATE(CGnssRefStationView, CListView)

CGnssRefStationView::CGnssRefStationView()
: m_curLine(0)
{
	m_fontItem.CreateFont(
		15,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("����"));
}

CGnssRefStationView::~CGnssRefStationView()
{
}

BEGIN_MESSAGE_MAP(CGnssRefStationView, CListView)
END_MESSAGE_MAP()


// CGnssRefStationView ���

#ifdef _DEBUG
void CGnssRefStationView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CGnssRefStationView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGnssRefStationView ��Ϣ�������


void CGnssRefStationView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	this->m_curLine = 0;
	CListCtrl& list = GetListCtrl();

	list.ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	list.SetExtendedStyle(list.GetExtendedStyle() | LVS_EX_FLATSB | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	list.SetFont(&m_fontItem);

	CImageList imgList;
	imgList.Create(1, 14, ILC_COLOR, 0, 0);

	list.SetImageList(&imgList, LVSIL_STATE);

	imgList.Detach();

	for (int i = 0; i<sizeof(s_reportItems) / sizeof(REPORT_ITEM); ++i)
	{
		list.InsertColumn(i, s_reportItems[i].name, LVCFMT_LEFT, s_reportItems[i].width);
	}

	ReDrawList();
}


void CGnssRefStationView::ReDrawList()
{
	int i;
	CListCtrl& list = GetListCtrl();
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	//int relaNum = pMain->m_CPCarNum;
	CString showstr;
	list.SetRedraw(FALSE);
	//��������
	for (i = list.GetItemCount(); i >= -1; i--)
	{
		list.DeleteItem(i);
	}	

	/*
	CCarCPRelation* CPfinder;
	CPfinder = pMain->m_CPTerm;
	i = 0;
	while (CPfinder != NULL)
	{

		list.InsertItem(i, CPfinder->m_CompanyName);
		showstr.Format("%d", CPfinder->m_CarPort);
		list.SetItemText(i, INDEX_PORT, showstr);
		showstr.Format("%d", CPfinder->m_WholeCarNum);
		list.SetItemText(i, INDEX_ONLINE_CAR, showstr);
		showstr.Format("%.3fK", CPfinder->m_UpDataQ / 1024);
		list.SetItemText(i, INDEX_UPLOAD_FLOW, showstr);
		showstr.Format("%.3fK", CPfinder->m_DownDataQ / 1024);
		list.SetItemText(i, INDEX_DOWNLOAD_FLOW, showstr);

		if (CPfinder->m_WholeCarNum>0)
		{
			list.SetItemText(i, INDEX_STATUS, lpszSTATUS_CONNECT);
		}
		else
		{
			list.SetItemText(i, INDEX_STATUS, lpszSTATUS_UNCONNECT);
		}
		CPfinder = CPfinder->next;
		i++;
	}
	*/
	list.SetRedraw(TRUE);
	list.Invalidate();
	list.UpdateWindow();
}
