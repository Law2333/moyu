
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "moyu.h"
#include "SelectView.h"
#include "DisplayView.h"
#include "GrayImgDlg.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//�ֽ���м����Զ�����Ϣ
	//ON_MESSAGE��Ӧ�Զ�����Ϣ
	//����NM_X��Ϣ���Զ�����OnMyChange����
	ON_MESSAGE(NM_SHOWIMG, OnMyChange)
	ON_MESSAGE(NM_GRAYIMG, OnMyChange)
	ON_MESSAGE(NM_BINARYIMG, OnMyChange)

	ON_COMMAND(ID_32771, &CMainFrame::OnMainExit)
	ON_COMMAND(ID_32773, &CMainFrame::OnChangeShowTyle)
	ON_UPDATE_COMMAND_UI(ID_32773, &CMainFrame::OnUpdateChangeShowTyle)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//����ͼ��
	SetClassLongPtr(m_hWnd, GCLP_HICON, (LONG_PTR)AfxGetApp()->LoadIconW(IDI_ICON_TITLE));
	//���ñ��� ������
	SetTitle(TEXT("������"));

	//���ô��ڴ�С
	MoveWindow(300, 300, 800, 500);
	//������ʾ
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���


	//return CFrameWnd::OnCreateClient(lpcs, pContext);

	//���һ������
	m_spliter.CreateStatic(this, 1, 2);

	//�����Ҳ��������
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500), pContext);
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 500), pContext);

	return TRUE;		//�Լ����
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext Context;
	if (wParam == NM_SHOWIMG)
	{
		//���ؽ���
		Context.m_pNewViewClass = RUNTIME_CLASS(CShowImgDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CShowImgDlg), CSize(900, 600), &Context);
		CShowImgDlg *pNewView = (CShowImgDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_GRAYIMG)
	{
		Context.m_pNewViewClass = RUNTIME_CLASS(CGrayImgDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CGrayImgDlg), CSize(900, 600), &Context);
		CGrayImgDlg *pNewView = (CGrayImgDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_BINARYIMG)
	{
		Context.m_pNewViewClass = RUNTIME_CLASS(CBinaryImgDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CBinaryImgDlg), CSize(900, 600), &Context);
		CBinaryImgDlg *pNewView = (CBinaryImgDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}


	return LRESULT();
}


//�˳���ť
void CMainFrame::OnMainExit()
{
	// TODO: �ڴ���������������
	exit(0);

}

//�˵���ͼƬ��ʾģʽ
void CMainFrame::OnChangeShowTyle()
{
	// TODO: �ڴ���������������
	winShowType = !winShowType;
}
void CMainFrame::OnUpdateChangeShowTyle(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������

	pCmdUI->SetCheck(!winShowType);
}