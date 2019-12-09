// ShowImgDlg.cpp : 实现文件
// 图片显示的实现

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
	ON_BN_CLICKED(IDC_CUTBUTTON2, &CShowImgDlg::OnBnClickedCutbutton)
	ON_BN_CLICKED(IDC_SAVEBUTTON, &CShowImgDlg::OnBnClickedSavebutton)
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
	sWnd = this->GetSafeHwnd();		//获取句柄
	CPublic::ShowMat(image, sWnd, IDC_SHOWIMG);

	//保留图片显示状态
	drawFlag = 1;

	UpdateData(false);

}


//重写OnPaint维持图像一直显示
void CShowImgDlg::OnPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CFormView::OnPaint()
	
	CFormView::OnPaint();
	//按下显示按钮，图片维持显示状态
	if (drawFlag)
	{
		CPublic::ShowMat(image, sWnd, IDC_SHOWIMG);
	}
	else if (drawCutFlag)
	{
		CPublic::ShowMat(cutImg, sWnd, IDC_SHOWIMG);
	}

}

//裁剪按钮响应
void CShowImgDlg::OnBnClickedCutbutton()
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

	//pic控件中显示Mat
	sWnd = this->GetSafeHwnd();		//获取句柄
	CPublic::ShowMat(image, sWnd, IDC_SHOWIMG);

	//裁剪ROI
	cv::Rect roi;
	roi = cv::selectROI(image);
	cutImg = image(roi);

	if (cutImg.empty())
	{
		AfxMessageBox(_T("图片裁剪失败"));
		return;
	}
	else
	{
		MessageBox(_T("裁剪成功"));
	}

	imshow("cut", cutImg);

	//改变控件显示的图片
	drawFlag = 0;
	drawCutFlag = 1;
	sWnd = this->GetSafeHwnd();		//获取句柄
	CPublic::ShowMat(cutImg, sWnd, IDC_SHOWIMG);

}

//dlg循环捕获
BOOL CShowImgDlg::PreTranslateMessage(MSG * pMsg)
{
	//截获键盘输入
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
			//esc关闭所有弹出图像窗口
			//MessageBox(_T("esc")); break;
			cv::destroyAllWindows();

		default:
			break;
		}
	}

	//__super指代父类
	return __super::PreTranslateMessage(pMsg);
}

//dlg初始化更新
void CShowImgDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	CWnd *pWnd;
	//pic控件位置确定
	pWnd = GetDlgItem(IDC_SHOWIMG); //获取控件指针，IDC_SHOWIMG为控件ID号
	pWnd->MoveWindow(CRect(60, 260, 760, 960)); 

	pWnd = GetDlgItem(IDC_STATICPIC); //获取控件指针，IDC_SHOWIMG为控件ID号
	pWnd->MoveWindow(CRect(50, 240, 770, 970));
}

//保存图片按钮
void CShowImgDlg::OnBnClickedSavebutton()
{
	// TODO: 在此添加控件通知处理程序代码
	//检查图片是否已读取
	if (cutImg.empty())
	{
		AfxMessageBox(_T("无法读取图片"));
		return;
	}

	TCHAR imgFilter[] = _T("png文件(*.png)|*.png|JPEG文件(*.jpg)|*.jpg||");
	// 构造保存文件对话框
	CFileDialog fileDlg(FALSE, _T("png"), _T("cut"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, imgFilter, this);
	CString filePath;
	// 显示保存文件对话框
	if (IDOK == fileDlg.DoModal())
	{
		filePath = fileDlg.GetPathName();
		std::string tempPath = (LPCSTR)CStringA(filePath);
		cv::imwrite(tempPath, cutImg);

		MessageBox(_T("保存成功"));
	}

	return;

}
