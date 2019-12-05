
// MainFrm.cpp : CMainFrame 类的实现
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

	//分界宏中加入自定义消息
	//ON_MESSAGE响应自定义消息
	//产生NM_X消息，自动调用OnMyChange函数
	ON_MESSAGE(NM_SHOWIMG, OnMyChange)
	ON_MESSAGE(NM_GRAYIMG, OnMyChange)
	ON_MESSAGE(NM_BINARYIMG, OnMyChange)

	ON_COMMAND(ID_32771, &CMainFrame::OnMainExit)
	ON_COMMAND(ID_32773, &CMainFrame::OnChangeShowTyle)
	ON_UPDATE_COMMAND_UI(ID_32773, &CMainFrame::OnUpdateChangeShowTyle)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
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
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//设置图标
	SetClassLongPtr(m_hWnd, GCLP_HICON, (LONG_PTR)AfxGetApp()->LoadIconW(IDI_ICON_TITLE));
	//设置标题 副标题
	SetTitle(TEXT("工具箱"));

	//设置窗口大小
	MoveWindow(300, 300, 800, 500);
	//居中显示
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类


	//return CFrameWnd::OnCreateClient(lpcs, pContext);

	//拆成一行两列
	m_spliter.CreateStatic(this, 1, 2);

	//左侧和右侧具体内容
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500), pContext);
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 500), pContext);

	return TRUE;		//自己拆分
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext Context;
	if (wParam == NM_SHOWIMG)
	{
		//挂载界面
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


//退出按钮
void CMainFrame::OnMainExit()
{
	// TODO: 在此添加命令处理程序代码
	exit(0);

}

//菜单栏图片显示模式
void CMainFrame::OnChangeShowTyle()
{
	// TODO: 在此添加命令处理程序代码
	winShowType = !winShowType;
}
void CMainFrame::OnUpdateChangeShowTyle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	pCmdUI->SetCheck(!winShowType);
}