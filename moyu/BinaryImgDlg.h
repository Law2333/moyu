#pragma once

#include "afxcmn.h"
#include "afxwin.h"



// CBinaryImgDlg 窗体视图
class CBinaryImgDlg : public CFormView
{
	DECLARE_DYNCREATE(CBinaryImgDlg)

protected:
	CBinaryImgDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CBinaryImgDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINARYIMGDLG };
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

private:
	cv::Mat srcImg,dstImg;		//原图片，阈值化图片
	int drawFlag = 0;	//是否源图片的标志
	int drawThFlag = 0;	//是否阈值图片的标志
	HWND sWnd;			//窗口句柄

	CSliderCtrl m_maxSlider;
	CSliderCtrl m_minSlider;
	CEdit m_maxEdit;
	CEdit m_minEdit;
public:
	afx_msg void OnNMCustomdrawMaxslider(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnInitialUpdate();
	afx_msg void OnNMCustomdrawMinslider(NMHDR *pNMHDR, LRESULT *pResult);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedProcessbutton();
	afx_msg void OnBnClickedSavebutton();
private:
	CComboBox m_typeCombox;
	CComboBox m_methodCombox;
public:
	afx_msg void OnPaint();
};


