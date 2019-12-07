// GrayImgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "moyu.h"
#include "GrayImgDlg.h"
#include "public.h"

// CGrayImgDlg

IMPLEMENT_DYNCREATE(CGrayImgDlg, CFormView)

CGrayImgDlg::CGrayImgDlg()
	: CFormView(IDD_GRAYDLG)
{
	srcImgs.resize(30);
	dstImgs.resize(30);
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
	
	//��������ļ�·������
	const DWORD numberOfFileNames = 32;
	const DWORD fileNameMaxLength = MAX_PATH + 1;
	//��������С
	const DWORD bufferSize = (numberOfFileNames * fileNameMaxLength) + 1;
	//�ļ���·���Ļ�����
	TCHAR* filenamesBuffer = new TCHAR[bufferSize];

	//��ʼ��������ͷβ
	filenamesBuffer[0] = NULL;//�����
	filenamesBuffer[bufferSize - 1] = NULL;


	//�ļ�����˵������չ������ | �ָ���ÿ���ļ����ͼ��� | �ָ���ĩβ�� || ָ����
	TCHAR imgFilter[] = _T("png�ļ�(*.png)|*.png|JPEG�ļ�(*.jpg)|*.jpg||");
	//��ȡ�ļ�·��,OFN_ALLOWMULTISELECT�����ѡ
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT | OFN_EXPLORER, imgFilter, this);

	//���������Ը�ֵ���ļ��Ի���, m_ofn�������öԻ����һЩ����
	fileDlg.m_ofn.lpstrFile = filenamesBuffer;
	fileDlg.m_ofn.nMaxFile = bufferSize;
	
	//����ļ�·������
	fileNameVector.clear();
	//�ļ�·����������
	int numFile = 0;
	//��ʾ�ļ��Ի���
	if (IDOK == fileDlg.DoModal())
	{
		CString picName;
		POSITION pos = fileDlg.GetStartPosition();
		while (pos != NULL)
		{
			picName = fileDlg.GetNextPathName(pos);//����ѡ���ļ��ļ���
			fileNameVector.push_back(picName);
			numFile++;	
			//ͼƬ·�������ı���
			m_fileEdit.SetWindowTextW(picName);
			if (numFile > 30)
			{
				AfxMessageBox(_T("ѡ���ͼƬ��������30!"));
				return ;
			}
		}
	}

	//�ͷŻ�����
	delete[] filenamesBuffer;

	UpdateData(false);
}


void CGrayImgDlg::OnBnClickedGraybutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//����ͼƬ��
	srcImgs.clear();
	dstImgs.clear();
	srcImgs.resize(30);
	dstImgs.resize(30);

	CString errMsg, tempName;
	std::string tempPath,strWinName;
	for (int i = 0;i < fileNameVector.size();i++)
	{	
		strWinName.clear();
		//���ļ�·��vector��ȡ·��
		tempPath = (LPCSTR)CStringA(fileNameVector[i]);
		//��ȡͼƬ
		srcImgs[i] = cv::imread(tempPath);
		if (srcImgs[i].empty())
		{
			errMsg.Format(_T("%sͼƬ��ʧ��"),tempPath);
			AfxMessageBox(errMsg);
			return;
		}
		//�Ҷȴ���
		cv::cvtColor(srcImgs[i], dstImgs[i], cv::COLOR_BGR2GRAY);
		//���ͼƬ�Ƿ�ת���洢�ɹ�
		if (dstImgs[i].empty())
		{
			errMsg.Format(_T("%sͼƬת��ʧ��"), tempPath);
			AfxMessageBox(errMsg);
			return;
		}

		//���ô��ڸ�ʽ
		tempName.Format(_T("%d"), i);
		cv::namedWindow(strWinName.append("image_").append((LPCSTR)CStringA(tempName)), CPublic::winShowType);
		//��ʾͼƬ
		cv::imshow(strWinName, dstImgs[i]);
	}
	MessageBox(_T("�Ҷȴ������"));


	UpdateData(false);
}


void CGrayImgDlg::OnBnClickedSavebutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	TCHAR imgFilter[] = _T("png�ļ�(*.png)|*.png|JPEG�ļ�(*.jpg)|*.jpg||");
	// ���챣���ļ��Ի���
	CFileDialog fileDlg(FALSE, _T("png"), _T("gray"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, imgFilter, this);

	CString filePath,tempName;
	std::string tempPath;

	// ��ʾ�����ļ��Ի���
	if (IDOK == fileDlg.DoModal())
	{
		for (int i = 0; i < fileNameVector.size(); i++)
		{
			//��ȡ·����ת��
			filePath = fileDlg.GetPathName();
			tempName.Format(_T("%d"), i);
			tempPath = (LPCSTR)CStringA(filePath);
			//�����ļ���
			tempPath.insert(tempPath.rfind("."), (LPCSTR)CStringA(tempName));
			cv::imwrite(tempPath, dstImgs[i]);
		}
		MessageBox(_T("����ɹ�"));
	}

	return;
}

