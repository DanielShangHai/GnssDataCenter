// GnssClientView.cpp : 实现文件
//

#include "stdafx.h"
#include "GNSSRefDataCenter.h"
#include "GnssClientView.h"
#include "MainFrm.h"
#include "GNSSRefDataCenter.h"

typedef struct tagREPORT_ITEM
{
	LPCTSTR name;
	int     width;
} REPORT_ITEM, *LPREPORT_ITEM;

const REPORT_ITEM s_reportItems[] =
{
	{ _T("用户终端"), 100 },
	{ _T("IP地址"), 100 },
	{ _T("申请源"), 100 },
	{ _T("下发流量(字节数)"), 140 },
	{ _T("上传流量(字节数)"), 140 },
	{ _T("总流量(字节数)"), 140 },
	{ _T("状态"), 100 },
};


#define INDEX_USER              0        
#define INDEX_IP                1        
#define INDEX_UPLOAD_FLOW       3
#define INDEX_DOWNLOAD_FLOW     2
#define INDEX_TOTAL             4
#define INDEX_STATUS            5

const TCHAR lpszGSTATUS_UNCONNECT[] = _T("未连接");
const TCHAR lpszGSTATUS_CONNECT[] = _T("己连接");




// CGnssClientView

IMPLEMENT_DYNCREATE(CGnssClientView, CListView)

CGnssClientView::CGnssClientView()
: m_nowCPLine(0)
, m_nowCPcol(0)
, m_curLine(0)
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
		_T("宋体"));
	this->m_nowCPLine = 0;
	this->m_nowCPcol = 0;
}

CGnssClientView::~CGnssClientView()
{
}

BEGIN_MESSAGE_MAP(CGnssClientView, CListView)
END_MESSAGE_MAP()


// CGnssClientView 诊断

#ifdef _DEBUG
void CGnssClientView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CGnssClientView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGnssClientView 消息处理程序


void CGnssClientView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
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
	this->m_curLine = 0;
	//ReDrawList();

}
