// SelectView.cpp : 实现文件
//

#include "stdafx.h"
#include "moyu.h"
#include "SelectView.h"
#include "MainFrm.h"


// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//初始化树视图
	//获取树控件
	m_treeCtrl = &GetTreeCtrl();

	//图片集合
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON_TREE);

	m_imageList.Create(40, 40, ILC_COLOR32, 1, 1);
	m_imageList.Add(icon);
	m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);

	//添加节点,最后一个参数父节点
	m_treeCtrl->InsertItem(_T("图像裁剪"),0,0,NULL);
	m_treeCtrl->InsertItem(_T("图像灰度处理"), 0, 0, NULL);
	m_treeCtrl->InsertItem(_T("图像二值化"), 0, 0, NULL);

}


void CSelectView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//获取选中项
	HTREEITEM item = m_treeCtrl->GetSelectedItem();
	//通过选中项 获取这个项中的内容
	CString str = m_treeCtrl->GetItemText(item);

	//MessageBox(str);
	if (str == TEXT("图像裁剪"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_SHOWIMG, (WPARAM)NM_SHOWIMG, (LPARAM)0);
	}
	else if (str == TEXT("图像灰度处理"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_GRAYIMG, (WPARAM)NM_GRAYIMG, (LPARAM)0);
	}
	else if (str == TEXT("图像二值化"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_BINARYIMG, (WPARAM)NM_BINARYIMG, (LPARAM)0);
	}	
/*	else if (str == TEXT("干员标签信息"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
	}*/	

}
