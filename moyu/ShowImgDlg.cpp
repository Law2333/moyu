// ShowImgDlg.cpp : ʵ���ļ�
//
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
END_MESSAGE_MAP()


// CShowImgDlg ���

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


// CShowImgDlg ��Ϣ�������


void CShowImgDlg::OnBnClickedChoosebutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//�ļ�����˵������չ������ | �ָ���ÿ���ļ����ͼ��� | �ָ���ĩβ�� || ָ����
	TCHAR imgFilter[] = _T("png�ļ�(*.png)|*.png|JPEG�ļ�(*.jpg)|*.jpg||");

	//��ȡ�ļ�·��
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, imgFilter, this);
    fileDlg.DoModal();
	CString filePath=fileDlg.GetPathName();		//�ļ�·��
	if (filePath == _T(""))
    {
        return;
    }
	//ͼƬ·������1�ı���
	m_fileEdit.SetWindowTextW(filePath);

	UpdateData(false);
}


void CShowImgDlg::OnBnClickedOpenbutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//���ı����ȡ·��
	CString filePath;
	m_fileEdit.GetWindowTextW(filePath);
	std::string tempPath = (LPCSTR)CStringA(filePath);

	//��ȡͼƬ
    image = cv::imread(tempPath);
	if (image.empty())
	{
		AfxMessageBox(_T("�޷���ͼƬ"));
		return;
	}

	//���ô��ڸ�ʽ
	cv::namedWindow("image", CPublic::winShowType);
	cv::imshow("image", image);

	//pic�ؼ�����ʾMat
	HWND sWnd = this->GetSafeHwnd();
	CPublic::ShowMat(image, sWnd, IDC_SHOWIMG);

	//����ͼƬ��ʾ״̬
	drawFlag = 1;

	UpdateData(false);

}





void CShowImgDlg::OnPaint()
{
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()
	
	CFormView::OnPaint();
	//������ʾ��ť��ͼƬά����ʾ״̬
	if (drawFlag)
	{
		HWND sWnd = this->GetSafeHwnd();
		CPublic::ShowMat(image, sWnd, IDC_SHOWIMG);
	}

}
