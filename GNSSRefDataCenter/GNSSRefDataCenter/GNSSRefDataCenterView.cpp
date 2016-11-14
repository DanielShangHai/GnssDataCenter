
// GNSSRefDataCenterView.cpp : CGNSSRefDataCenterView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "GNSSRefDataCenter.h"
#endif

#include "GNSSRefDataCenterDoc.h"
#include "GNSSRefDataCenterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGNSSRefDataCenterView

IMPLEMENT_DYNCREATE(CGNSSRefDataCenterView, CView)

BEGIN_MESSAGE_MAP(CGNSSRefDataCenterView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGNSSRefDataCenterView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGNSSRefDataCenterView ����/����

CGNSSRefDataCenterView::CGNSSRefDataCenterView()
{
	// TODO:  �ڴ˴���ӹ������

}

CGNSSRefDataCenterView::~CGNSSRefDataCenterView()
{
}

BOOL CGNSSRefDataCenterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGNSSRefDataCenterView ����

void CGNSSRefDataCenterView::OnDraw(CDC* /*pDC*/)
{
	CGNSSRefDataCenterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CGNSSRefDataCenterView ��ӡ


void CGNSSRefDataCenterView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGNSSRefDataCenterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGNSSRefDataCenterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGNSSRefDataCenterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CGNSSRefDataCenterView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGNSSRefDataCenterView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGNSSRefDataCenterView ���

#ifdef _DEBUG
void CGNSSRefDataCenterView::AssertValid() const
{
	CView::AssertValid();
}

void CGNSSRefDataCenterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGNSSRefDataCenterDoc* CGNSSRefDataCenterView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGNSSRefDataCenterDoc)));
	return (CGNSSRefDataCenterDoc*)m_pDocument;
}
#endif //_DEBUG


// CGNSSRefDataCenterView ��Ϣ�������
