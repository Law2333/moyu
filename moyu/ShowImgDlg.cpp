// ShowImgDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "ShowImgDlg.h"
#include "moyu.h"
#include "public.h"

// CShowImgDlg

IMPLEMENT_DYNCREATE(CShowImgDlg, CFormView)

CShowImgDlg::CShowImgDlg()
	: CFormView(IDD_SHOWIMG)
{

}

CShowImgDlg::~CShowImgDlg()
{
}

void CShowImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPENEDIT, m_fileEdit);
	DDX_Control(pDX, IDC_SHOWIMG, m_showImgP);
}

BEGIN_MESSAGE_MAP(CShowImgDlg, CFormView)
	ON_BN_CLICKED(IDC_CHOOSEBUTTON, &CShowImgDlg::OnBnClickedChoosebutton)
	ON_BN_CLICKED(IDC_OPENBUTTON, &CShowImgDlg::OnBnClickedOpenbutton)

	ON_WM_PAINT()
END_MESSAGE_MAP()


// CShowImgDlg 诊断

#ifdef _DEBUG
void CShowImgDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowImgDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowImgDlg 消息处理程序


void CShowImgDlg::OnBnClickedChoosebutton()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//文件类型说明和扩展名间用 | 分隔，每种文件类型间用 | 分隔，末尾用 || 指明。
	TCHAR imgFilter[] = _T("png文件(*.png)|*.png|JPEG文件(*.jpg)|*.jpg||");

	//获取文件路径
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, imgFilter, this);
    fileDlg.DoModal();
	CString filePath=fileDlg.GetPathName();		//文件路径
	if (filePath == _T(""))
    {
        return;
    }
	//图片路径放入1文本框
	m_fileEdit.SetWindowTextW(filePath);

	UpdateData(false);
}


void CShowImgDlg::OnBnClickedOpenbutton()
{
	// TODO: 在此添加控件通知处理程序代码

	//从文本框获取路径
	CString filePath;
	m_fileEdit.GetWindowTextW(filePath);
	std::string tempPath = (LPCSTR)CStringA(filePath);

	//读取图片
    image = cv::imread(tempPath);
	if (image.empty())
	{
		AfxMessageBox(_T("无法打开图片"));
		return;
	}

	//设置窗口格式
	cv::namedWindow("image", CPublic::winShowType);
	cv::imshow("image", image);

	//pic控件中显示Mat
	HWND sWnd = this->GetSafeHwnd();
	CPublic::ShowMat(image, sWnd, IDC_SHOWIMG);

	//保留图片显示状态
	drawFlag = 1;

	UpdateData(false);

}





void CShowImgDlg::OnPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CFormView::OnPaint()
	
	CFormView::OnPaint();
	//按下显示按钮，图片维持显示状态
	if (drawFlag)
	{
		HWND sWnd = this->GetSafeHwnd();
		CPublic::ShowMat(image, sWnd, IDC_SHOWIMG);
	}

}
