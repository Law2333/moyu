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
	std::vector<cv::Mat> srcImg,dstImg;
public:
	afx_msg void OnBnClickedChoosebutton();
	afx_msg void OnBnClickedGraybutton();
	afx_msg void OnBnClickedSavebutton();
};


