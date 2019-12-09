// ShowImgDlg.cpp : ʵ���ļ�
// ͼƬ��ʾ��ʵ��

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
	ON_BN_CLICKED(IDC_CUTBUTTON2, &CShowImgDlg::OnBnClickedCutbutton)
	ON_BN_CLICKED(IDC_SAVEBUTTON, &CShowImgDlg::OnBnClickedSavebutton)
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
	sWnd = this->GetSafeHwnd();		//��ȡ���
	CPublic::ShowMat(image, sWnd, IDC_SHOWIMG);

	//����ͼƬ��ʾ״̬
	drawFlag = 1;

	UpdateData(false);

}


//��дOnPaintά��ͼ��һֱ��ʾ
void CShowImgDlg::OnPaint()
{
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()
	
	CFormView::OnPaint();
	//������ʾ��ť��ͼƬά����ʾ״̬
	if (drawFlag)
	{
		CPublic::ShowMat(image, sWnd, IDC_SHOWIMG);
	}
	else if (drawCutFlag)
	{
		CPublic::ShowMat(cutImg, sWnd, IDC_SHOWIMG);
	}

}

//�ü���ť��Ӧ
void CShowImgDlg::OnBnClickedCutbutton()
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

	//pic�ؼ�����ʾMat
	sWnd = this->GetSafeHwnd();		//��ȡ���
	CPublic::ShowMat(image, sWnd, IDC_SHOWIMG);

	//�ü�ROI
	cv::Rect roi;
	roi = cv::selectROI(image);
	cutImg = image(roi);

	if (cutImg.empty())
	{
		AfxMessageBox(_T("ͼƬ�ü�ʧ��"));
		return;
	}
	else
	{
		MessageBox(_T("�ü��ɹ�"));
	}

	imshow("cut", cutImg);

	//�ı�ؼ���ʾ��ͼƬ
	drawFlag = 0;
	drawCutFlag = 1;
	sWnd = this->GetSafeHwnd();		//��ȡ���
	CPublic::ShowMat(cutImg, sWnd, IDC_SHOWIMG);

}

//dlgѭ������
BOOL CShowImgDlg::PreTranslateMessage(MSG * pMsg)
{
	//�ػ��������
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
			//esc�ر����е���ͼ�񴰿�
			//MessageBox(_T("esc")); break;
			cv::destroyAllWindows();

		default:
			break;
		}
	}

	//__superָ������
	return __super::PreTranslateMessage(pMsg);
}

//dlg��ʼ������
void CShowImgDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	CWnd *pWnd;
	//pic�ؼ�λ��ȷ��
	pWnd = GetDlgItem(IDC_SHOWIMG); //��ȡ�ؼ�ָ�룬IDC_SHOWIMGΪ�ؼ�ID��
	pWnd->MoveWindow(CRect(60, 260, 760, 960)); 

	pWnd = GetDlgItem(IDC_STATICPIC); //��ȡ�ؼ�ָ�룬IDC_SHOWIMGΪ�ؼ�ID��
	pWnd->MoveWindow(CRect(50, 240, 770, 970));
}

//����ͼƬ��ť
void CShowImgDlg::OnBnClickedSavebutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ͼƬ�Ƿ��Ѷ�ȡ
	if (cutImg.empty())
	{
		AfxMessageBox(_T("�޷���ȡͼƬ"));
		return;
	}

	TCHAR imgFilter[] = _T("png�ļ�(*.png)|*.png|JPEG�ļ�(*.jpg)|*.jpg||");
	// ���챣���ļ��Ի���
	CFileDialog fileDlg(FALSE, _T("png"), _T("cut"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, imgFilter, this);
	CString filePath;
	// ��ʾ�����ļ��Ի���
	if (IDOK == fileDlg.DoModal())
	{
		filePath = fileDlg.GetPathName();
		std::string tempPath = (LPCSTR)CStringA(filePath);
		cv::imwrite(tempPath, cutImg);

		MessageBox(_T("����ɹ�"));
	}

	return;

}
