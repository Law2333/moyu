#pragma once
#include "afxwin.h"


// CShowImgDlg ������ͼ

class CShowImgDlg : public CFormView
{
	DECLARE_DYNCREATE(CShowImgDlg)

protected:
	CShowImgDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChoosebutton();
	afx_msg void OnBnClickedOpenbutton();

private:
	CEdit m_fileEdit;
	CStatic m_showImgP;

	cv::Mat image;		//��ȡ��ͼƬ
	int drawFlag = 0;	//�Ƿ���ʾͼƬ�ı�־
public:
	afx_msg void OnPaint();
};


