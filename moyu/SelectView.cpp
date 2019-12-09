// SelectView.cpp : ʵ���ļ�
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


// CSelectView ���

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


// CSelectView ��Ϣ�������


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	//��ʼ������ͼ
	//��ȡ���ؼ�
	m_treeCtrl = &GetTreeCtrl();

	//ͼƬ����
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON_TREE);

	m_imageList.Create(40, 40, ILC_COLOR32, 1, 1);
	m_imageList.Add(icon);
	m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);

	//��ӽڵ�,���һ���������ڵ�
	m_treeCtrl->InsertItem(_T("ͼ��ü�"),0,0,NULL);
	m_treeCtrl->InsertItem(_T("ͼ��Ҷȴ���"), 0, 0, NULL);
	m_treeCtrl->InsertItem(_T("ͼ���ֵ��"), 0, 0, NULL);

}


void CSelectView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	//��ȡѡ����
	HTREEITEM item = m_treeCtrl->GetSelectedItem();
	//ͨ��ѡ���� ��ȡ������е�����
	CString str = m_treeCtrl->GetItemText(item);

	//MessageBox(str);
	if (str == TEXT("ͼ��ü�"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_SHOWIMG, (WPARAM)NM_SHOWIMG, (LPARAM)0);
	}
	else if (str == TEXT("ͼ��Ҷȴ���"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_GRAYIMG, (WPARAM)NM_GRAYIMG, (LPARAM)0);
	}
	else if (str == TEXT("ͼ���ֵ��"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_BINARYIMG, (WPARAM)NM_BINARYIMG, (LPARAM)0);
	}	
/*	else if (str == TEXT("��Ա��ǩ��Ϣ"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
	}*/	

}
