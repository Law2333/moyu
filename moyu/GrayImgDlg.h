#pragma once
#include "afxwin.h"



// CGrayImgDlg ������ͼ

class CGrayImgDlg : public CFormView
{
	DECLARE_DYNCREATE(CGrayImgDlg)

protected:
	CGrayImgDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:	
	CEdit m_fileEdit;
	//���룬���ͼƬ��
	std::vector<cv::Mat> srcImgs,dstImgs;
	//����ļ�·��������
	std::vector<CString> fileNameVector;
public:
	afx_msg void OnBnClickedChoosebutton();
	afx_msg void OnBnClickedGraybutton();
	afx_msg void OnBnClickedSavebutton();
};


