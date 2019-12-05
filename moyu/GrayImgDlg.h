#pragma once
#include "afxwin.h"



// CGrayImgDlg 窗体视图

class CGrayImgDlg : public CFormView
{
	DECLARE_DYNCREATE(CGrayImgDlg)

protected:
	CGrayImgDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CGrayImgDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAYDLG };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:	
	CEdit m_fileEdit;
	//输入，输出图片集
	std::vector<cv::Mat> srcImgs,dstImgs;
	//存放文件路径的向量
	std::vector<CString> fileNameVector;
public:
	afx_msg void OnBnClickedChoosebutton();
	afx_msg void OnBnClickedGraybutton();
	afx_msg void OnBnClickedSavebutton();
};


