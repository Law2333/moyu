﻿// BinaryImgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "moyu.h"
#include "BinaryImgDlg.h"


// CBinaryImgDlg

IMPLEMENT_DYNCREATE(CBinaryImgDlg, CFormView)

CBinaryImgDlg::CBinaryImgDlg()
	: CFormView(IDD_BINARYIMGDLG)
{

}

CBinaryImgDlg::~CBinaryImgDlg()
{
}

void CBinaryImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAXSLIDER, m_maxSlider);
	DDX_Control(pDX, IDC_MINSLIDER, m_minSlider);
	DDX_Control(pDX, IDC_MAXEDIT, m_maxEdit);
	DDX_Control(pDX, IDC_MINEDIT, m_minEdit);
	DDX_Control(pDX, IDC_TYPECOMBO, m_typeCombox);
	DDX_Control(pDX, IDC_METHODCOMBO, m_methodCombox);
}

BEGIN_MESSAGE_MAP(CBinaryImgDlg, CFormView)
	ON_BN_CLICKED(IDC_CHOOSEBUTTON, &CBinaryImgDlg::OnBnClickedChoosebutton)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_MAXSLIDER, &CBinaryImgDlg::OnNMCustomdrawMaxslider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_MINSLIDER, &CBinaryImgDlg::OnNMCustomdrawMinslider)
	ON_BN_CLICKED(IDC_PROCESSBUTTON, &CBinaryImgDlg::OnBnClickedProcessbutton)
	ON_BN_CLICKED(IDC_SAVEBUTTON, &CBinaryImgDlg::OnBnClickedSavebutton)
END_MESSAGE_MAP()


// CBinaryImgDlg 诊断

#ifdef _DEBUG
void CBinaryImgDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBinaryImgDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBinaryImgDlg 消息处理程序

//选择图片按钮
void CBinaryImgDlg::OnBnClickedChoosebutton()
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
	std::string tempPath = (LPCSTR)CStringA(filePath);

	//读取图片
    srcImg = cv::imread(tempPath,cv::IMREAD_GRAYSCALE);
	if (srcImg.empty())
	{
		AfxMessageBox(_T("无法打开图片"));
		return;
	}

	cv::namedWindow("image", winShowType);
	cv::imshow("image", srcImg);

	UpdateData(false);
	return;
}

//阈值处理按钮
void CBinaryImgDlg::OnBnClickedProcessbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//检查图片是否已读取
	if (srcImg.empty())
	{
		AfxMessageBox(_T("无法打开图片"));
		return;
	}

	//获取阈值并检查
	int thresholdMin = m_minSlider.GetPos();
	int thresholdMax = m_maxSlider.GetPos();
	if (thresholdMax < thresholdMin)
	{
		AfxMessageBox(_T("最大阈值必须大于最小阈值!"));
		return;
	}

	int thresholdType = m_typeCombox.GetCurSel();
	int thresholdMethod = m_methodCombox.GetCurSel() * 8;

	cv::threshold(srcImg, dstImg, thresholdMin, thresholdMax, thresholdType|thresholdMethod);
	cv::namedWindow("阈值图像", winShowType);
	cv::imshow("阈值图像", dstImg);

	return;
}

//保存图片按钮
void CBinaryImgDlg::OnBnClickedSavebutton()
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
	CFileDialog fileDlg(FALSE, _T("png"), _T("threshold"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, imgFilter, this);
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

//初始化控件
void CBinaryImgDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//滑动条初始化
	m_maxSlider.SetRange(0, 255);
	m_minSlider.SetRange(0, 255);
	m_maxSlider.SetPos(255);
	m_minSlider.SetPos(0);

	//对应文本框初始化
	m_maxEdit.SetWindowTextW(_T("255"));
	m_minEdit.SetWindowTextW(_T("0"));

	//下拉框初始化
	m_typeCombox.SetCurSel(0);
	m_methodCombox.SetCurSel(0);

	return;
}

//最大阈值滑动条同步
void CBinaryImgDlg::OnNMCustomdrawMaxslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//同步对应文本框
	CString str;
	int value = m_maxSlider.GetPos();
	str.Format(_T("%d"), value);
	m_maxEdit.SetWindowTextW(str);

	return;
}

//最小阈值滑动条同步
void CBinaryImgDlg::OnNMCustomdrawMinslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//同步对应文本框
	CString str;
	int value = m_minSlider.GetPos();
	str.Format(_T("%d"), value);
	m_minEdit.SetWindowTextW(str);

	return;
}


//重写，获取键盘回车同步改变滑动条
BOOL CBinaryImgDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (WM_KEYFIRST <= pMsg-> message && pMsg-> message <= WM_KEYLAST)   
	{  
		//键盘回车响应
		if(pMsg-> wParam==VK_RETURN )   
		{  
			UpdateData(TRUE);  
			
			CString strMax;
			int valueMax;
			m_maxEdit.GetWindowTextW(strMax);
			valueMax = _ttoi(strMax);					//转换成int整数
			m_maxSlider.SetPos(valueMax);

			CString strMin;
			int valueMin;
			m_minEdit.GetWindowTextW(strMin);
			valueMin = _ttoi(strMin);					//转换成int整数
			m_minSlider.SetPos(valueMin);

		}   
	} 

	return CFormView::PreTranslateMessage(pMsg);
}




