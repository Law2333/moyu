// GrayImgDlg.cpp : 实现文件
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


// CGrayImgDlg 诊断

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


// CGrayImgDlg 消息处理程序


void CGrayImgDlg::OnBnClickedChoosebutton()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//最多允许文件路径长度
	const DWORD numberOfFileNames = 32;
	const DWORD fileNameMaxLength = MAX_PATH + 1;
	//缓冲区大小
	const DWORD bufferSize = (numberOfFileNames * fileNameMaxLength) + 1;
	//文件名路径的缓冲区
	TCHAR* filenamesBuffer = new TCHAR[bufferSize];

	//初始化缓冲区头尾
	filenamesBuffer[0] = NULL;//必须的
	filenamesBuffer[bufferSize - 1] = NULL;


	//文件类型说明和扩展名间用 | 分隔，每种文件类型间用 | 分隔，末尾用 || 指明。
	TCHAR imgFilter[] = _T("png文件(*.png)|*.png|JPEG文件(*.jpg)|*.jpg||");
	//获取文件路径,OFN_ALLOWMULTISELECT允许多选
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT | OFN_EXPLORER, imgFilter, this);

	//缓冲区属性赋值给文件对话框, m_ofn用于设置对话框的一些属性
	fileDlg.m_ofn.lpstrFile = filenamesBuffer;
	fileDlg.m_ofn.nMaxFile = bufferSize;
	
	//清空文件路径向量
	fileNameVector.clear();
	//文件路径数组索引
	int numFile = 0;
	//显示文件对话框
	if (IDOK == fileDlg.DoModal())
	{
		CString picName;
		POSITION pos = fileDlg.GetStartPosition();
		while (pos != NULL)
		{
			picName = fileDlg.GetNextPathName(pos);//返回选定文件文件名
			fileNameVector.push_back(picName);
			numFile++;	
			//图片路径放入文本框
			m_fileEdit.SetWindowTextW(picName);
			if (numFile > 30)
			{
				AfxMessageBox(_T("选择的图片数量大于30!"));
				return ;
			}
		}
	}

	//释放缓冲区
	delete[] filenamesBuffer;

	UpdateData(false);
}


void CGrayImgDlg::OnBnClickedGraybutton()
{
	// TODO: 在此添加控件通知处理程序代码

	//重置图片集
	srcImgs.clear();
	dstImgs.clear();
	srcImgs.resize(30);
	dstImgs.resize(30);

	CString errMsg, tempName;
	std::string tempPath,strWinName;
	for (int i = 0;i < fileNameVector.size();i++)
	{	
		strWinName.clear();
		//从文件路径vector获取路径
		tempPath = (LPCSTR)CStringA(fileNameVector[i]);
		//读取图片
		srcImgs[i] = cv::imread(tempPath);
		if (srcImgs[i].empty())
		{
			errMsg.Format(_T("%s图片打开失败"),tempPath);
			AfxMessageBox(errMsg);
			return;
		}
		//灰度处理
		cv::cvtColor(srcImgs[i], dstImgs[i], cv::COLOR_BGR2GRAY);
		//检查图片是否转换存储成功
		if (dstImgs[i].empty())
		{
			errMsg.Format(_T("%s图片转换失败"), tempPath);
			AfxMessageBox(errMsg);
			return;
		}

		//设置窗口格式
		tempName.Format(_T("%d"), i);
		cv::namedWindow(strWinName.append("image_").append((LPCSTR)CStringA(tempName)), CPublic::winShowType);
		//显示图片
		cv::imshow(strWinName, dstImgs[i]);
	}
	MessageBox(_T("灰度处理完成"));


	UpdateData(false);
}


void CGrayImgDlg::OnBnClickedSavebutton()
{
	// TODO: 在此添加控件通知处理程序代码

	TCHAR imgFilter[] = _T("png文件(*.png)|*.png|JPEG文件(*.jpg)|*.jpg||");
	// 构造保存文件对话框
	CFileDialog fileDlg(FALSE, _T("png"), _T("gray"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, imgFilter, this);

	CString filePath,tempName;
	std::string tempPath;

	// 显示保存文件对话框
	if (IDOK == fileDlg.DoModal())
	{
		for (int i = 0; i < fileNameVector.size(); i++)
		{
			//获取路径并转换
			filePath = fileDlg.GetPathName();
			tempName.Format(_T("%d"), i);
			tempPath = (LPCSTR)CStringA(filePath);
			//更正文件名
			tempPath.insert(tempPath.rfind("."), (LPCSTR)CStringA(tempName));
			cv::imwrite(tempPath, dstImgs[i]);
		}
		MessageBox(_T("保存成功"));
	}

	return;
}

