#pragma once

#include "afxcmn.h"
#include "afxwin.h"



// CBinaryImgDlg ������ͼ
class CBinaryImgDlg : public CFormView
{
	DECLARE_DYNCREATE(CBinaryImgDlg)

protected:
	CBinaryImgDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChoosebutton();

private:
	cv::Mat srcImg,dstImg;		//ԭͼƬ����ֵ��ͼƬ
	int drawFlag = 0;	//�Ƿ�ԴͼƬ�ı�־
	int drawThFlag = 0;	//�Ƿ���ֵͼƬ�ı�־
	HWND sWnd;			//���ھ��

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


