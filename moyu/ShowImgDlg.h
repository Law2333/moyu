#pragma once
#include "afxwin.h"


// CShowImgDlg 窗体视图

class CShowImgDlg : public CFormView
{
	DECLARE_DYNCREATE(CShowImgDlg)

protected:
	CShowImgDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CShowImgDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOWIMG };
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
public:
	afx_msg void OnBnClickedChoosebutton();
	afx_msg void OnBnClickedOpenbutton();

private:
	CEdit m_fileEdit;
	CStatic m_showImgP;

	cv::Mat image;		//读取的图片
	int drawFlag = 0;	//是否显示图片的标志
public:
	afx_msg void OnPaint();
};


