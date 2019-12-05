// GrayImgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "moyu.h"
#include "GrayImgDlg.h"


// CGrayImgDlg

IMPLEMENT_DYNCREATE(CGrayImgDlg, CFormView)

CGrayImgDlg::CGrayImgDlg()
	: CFormView(IDD_GRAYDLG)
{

}

CGrayImgDlg::~CGrayImgDlg()
{
}

void CGrayImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILEEDIT, m_fileEdit);
}

BEGIN_MESSAGE_MAP(CGrayImgDlg, CFormView)
	ON_BN_CLICKED(IDC_CHOOSEBUTTON, &CGrayImgDlg::OnBnClickedChoosebutton)
	ON_BN_CLICKED(IDC_GRAYBUTTON, &CGrayImgDlg::OnBnClickedGraybutton)
	ON_BN_CLICKED(IDC_SAVEBUTTON, &CGrayImgDlg::OnBnClickedSavebutton)
END_MESSAGE_MAP()


// CGrayImgDlg 诊断

#ifdef _DEBUG
void CGrayImgDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGrayImgDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGrayImgDlg 消息处理程序


void CGrayImgDlg::OnBnClickedChoosebutton()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//最多允许32个文件,以及文件路径长度
	const DWORD numberOfFileNames = 32;
	const DWORD fileNameMaxLength = MAX_PATH + 1;
	//缓冲区大小
	const DWORD bufferSize = (numberOfFileNames * fileNameMaxLength) + 1;

	// Create array for file names.
	CString fileNameArray[numberOfFileNames];
	//文件类型说明和扩展名间用 | 分隔，每种文件类型间用 | 分隔，末尾用 || 指明。
	TCHAR imgFilter[] = _T("png文件(*.png)|*.png|JPEG文件(*.jpg)|*.jpg||");
	//获取文件路径,OFN_ALLOWMULTISELECT允许多选
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT | OFN_EXPLORER, imgFilter, this);
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


void CGrayImgDlg::OnBnClickedGraybutton()
{
	// TODO: 在此添加控件通知处理程序代码

	//从文本框获取路径
	CString filePath;
	m_fileEdit.GetWindowTextW(filePath);
	std::string tempPath = (LPCSTR)CStringA(filePath);

	//读取图片
    srcImg = cv::imread(tempPath);
	if (srcImg.empty())
	{
		AfxMessageBox(_T("无法打开图片"));
		return;
	}
	//灰度处理
	cv::cvtColor(srcImg, dstImg, cv::COLOR_BGR2GRAY);

	//设置窗口格式
	cv::namedWindow("image", winShowType);
	cv::imshow("image", dstImg);

	UpdateData(false);
}


void CGrayImgDlg::OnBnClickedSavebutton()
{
	// TODO: 在此添加控件通知处理程序代码

	
	//检查图片是否已读取
	if (dstImg.empty())
	{
		AfxMessageBox(_T("无法读取图片"));
		return;
	}

	TCHAR imgFilter[] = _T("png文件(*.png)|*.png|JPEG文件(*.jpg)|*.jpg||");
	// 构造保存文件对话框
	CFileDialog fileDlg(FALSE, _T("png"), _T("gray"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, imgFilter, this);
	CString filePath;
	// 显示保存文件对话框
	if (IDOK == fileDlg.DoModal())
	{
		filePath = fileDlg.GetPathName();
		std::string tempPath = (LPCSTR)CStringA(filePath);
		cv::imwrite(tempPath,dstImg);

		MessageBox(_T("保存成功"));
	}	

	return;
}

