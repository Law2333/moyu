// GrayImgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "moyu.h"
#include "GrayImgDlg.h"


// CGrayImgDlg

IMPLEMENT_DYNCREATE(CGrayImgDlg, CFormView)

CGrayImgDlg::CGrayImgDlg()
	: CFormView(IDD_GRAYDLG)
{

}

CGrayImgDlg::~CGrayImgDlg()
{
}

void CGrayImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILEEDIT, m_fileEdit);
}

BEGIN_MESSAGE_MAP(CGrayImgDlg, CFormView)
	ON_BN_CLICKED(IDC_CHOOSEBUTTON, &CGrayImgDlg::OnBnClickedChoosebutton)
	ON_BN_CLICKED(IDC_GRAYBUTTON, &CGrayImgDlg::OnBnClickedGraybutton)
	ON_BN_CLICKED(IDC_SAVEBUTTON, &CGrayImgDlg::OnBnClickedSavebutton)
END_MESSAGE_MAP()


// CGrayImgDlg ���

#ifdef _DEBUG
void CGrayImgDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGrayImgDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGrayImgDlg ��Ϣ�������


void CGrayImgDlg::OnBnClickedChoosebutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//�������32���ļ�,�Լ��ļ�·������
	const DWORD numberOfFileNames = 32;
	const DWORD fileNameMaxLength = MAX_PATH + 1;
	//��������С
	const DWORD bufferSize = (numberOfFileNames * fileNameMaxLength) + 1;

	// Create array for file names.
	CString fileNameArray[numberOfFileNames];
	//�ļ�����˵������չ������ | �ָ���ÿ���ļ����ͼ��� | �ָ���ĩβ�� || ָ����
	TCHAR imgFilter[] = _T("png�ļ�(*.png)|*.png|JPEG�ļ�(*.jpg)|*.jpg||");
	//��ȡ�ļ�·��,OFN_ALLOWMULTISELECT�����ѡ
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT | OFN_EXPLORER, imgFilter, this);
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


void CGrayImgDlg::OnBnClickedGraybutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//���ı����ȡ·��
	CString filePath;
	m_fileEdit.GetWindowTextW(filePath);
	std::string tempPath = (LPCSTR)CStringA(filePath);

	//��ȡͼƬ
    srcImg = cv::imread(tempPath);
	if (srcImg.empty())
	{
		AfxMessageBox(_T("�޷���ͼƬ"));
		return;
	}
	//�Ҷȴ���
	cv::cvtColor(srcImg, dstImg, cv::COLOR_BGR2GRAY);

	//���ô��ڸ�ʽ
	cv::namedWindow("image", winShowType);
	cv::imshow("image", dstImg);

	UpdateData(false);
}


void CGrayImgDlg::OnBnClickedSavebutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	
	//���ͼƬ�Ƿ��Ѷ�ȡ
	if (dstImg.empty())
	{
		AfxMessageBox(_T("�޷���ȡͼƬ"));
		return;
	}

	TCHAR imgFilter[] = _T("png�ļ�(*.png)|*.png|JPEG�ļ�(*.jpg)|*.jpg||");
	// ���챣���ļ��Ի���
	CFileDialog fileDlg(FALSE, _T("png"), _T("gray"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, imgFilter, this);
	CString filePath;
	// ��ʾ�����ļ��Ի���
	if (IDOK == fileDlg.DoModal())
	{
		filePath = fileDlg.GetPathName();
		std::string tempPath = (LPCSTR)CStringA(filePath);
		cv::imwrite(tempPath,dstImg);

		MessageBox(_T("����ɹ�"));
	}	

	return;
}

