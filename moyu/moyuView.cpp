
// moyuView.cpp : CmoyuView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "moyu.h"
#endif

#include "moyuDoc.h"
#include "moyuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmoyuView

IMPLEMENT_DYNCREATE(CmoyuView, CView)

BEGIN_MESSAGE_MAP(CmoyuView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CmoyuView ����/����

CmoyuView::CmoyuView()
{
	// TODO: �ڴ˴���ӹ������

}

CmoyuView::~CmoyuView()
{
}

BOOL CmoyuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CmoyuView ����

void CmoyuView::OnDraw(CDC* /*pDC*/)
{
	CmoyuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CmoyuView ��ӡ

BOOL CmoyuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CmoyuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CmoyuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CmoyuView ���

#ifdef _DEBUG
void CmoyuView::AssertValid() const
{
	CView::AssertValid();
}

void CmoyuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmoyuDoc* CmoyuView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmoyuDoc)));
	return (CmoyuDoc*)m_pDocument;
}
#endif //_DEBUG


// CmoyuView ��Ϣ�������
