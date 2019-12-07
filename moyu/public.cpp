//-----public.cpp----
//一些全局变量和函数的实现

#include "stdafx.h"
#include "public.h"


//初始化全局变量
int CPublic::winShowType = 1;



void CPublic::ShowMat(cv::Mat vMat, HWND hDlg, int vIDC)
{
	if (vMat.empty()) {
		return;
	}

	//获取图片的宽 高度
	int tImgWidth = vMat.cols;
	int tImgHeight = vMat.rows;
	//获取Picture Control控件的大小
	CRect rect;
	GetClientRect(GetDlgItem(hDlg,vIDC),&rect);

	//将客户区选中到控件表示的矩形区域内
	//ScreenToClient(&rect);

	//CString msg;
	//msg.Format(_T("tImgWidth=%d,tImgHeight=%d, rect：w=%d, h=%d"), tImgWidth, tImgHeight, rect.Width(), rect.Height());
	//MessageBox(msg, _T("showMat"), MB_OK); 

	//适用于控件的图像宽高
	int tNewWidth, tNewHeight;
	//绘制图像时2点的位置
	int tLeft = 0, tTop = 0, tRight = rect.Width(), tBottom = rect.Height();
	if (tImgWidth > tImgHeight) {
		//如果图像是横的
		tNewWidth = rect.Width();
		tNewHeight = tNewWidth * tImgHeight / tImgWidth;
		tTop = (rect.Height() - tNewHeight) / 2;
		tBottom = rect.Height() - tTop;
	}
	else {
		//如果图像是竖的
		tNewHeight = tBottom;
		tNewWidth = tNewHeight * tImgWidth / tImgHeight;
		tLeft = (rect.Width() - tNewWidth) / 2;
		tRight = rect.Width() - tLeft;
	}

	cv::Mat zoomImg;
	cv::resize(vMat, zoomImg, cv::Size(tNewWidth - 1, tNewHeight - 1));

	//把opencv的图转为CImage,才能显示在图像控件上
	CImage cimg;
	MatToCImage(zoomImg, cimg);

	//msg.Format(_T("neww=%d, newh=%d"), cimg.GetWidth(), cimg.GetHeight());
	//MessageBox(msg, _T("mm"), MB_OK); 

	///-----------------------------------------------------------------
	//以下是显示
	HWND pWnd = NULL;
	pWnd = GetDlgItem(hDlg, vIDC);//获取控件句柄 

	HDC pDc = NULL;
	pDc = GetDC(pWnd);//获取picture的DC

						//白色背景填充,保留边框
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	
	CRect tRect = CRect(1, 1, rect.Width() - 2, rect.Height() - 2);
	FillRect(pDc,tRect, brush);
	cimg.Draw(pDc, CRect(tLeft + 1, tTop + 1, tRight - 1, tBottom - 1));

	//删除画刷
	DeleteObject(brush);
	//释放DC
	ReleaseDC(pWnd,pDc);
	//msg.Format(_T("tLeft=%d,tTop=%d, tRight=%d,tBottom=%d"), tLeft, tTop, tRight, tBottom);
	//MessageBox(msg, _T("showMat"), MB_OK);
}


void CPublic::MatToCImage(cv::Mat& mat, CImage& cImage)
{
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	cImage.Destroy();//这一步是防止重复利用造成内存问题
	cImage.Create(width, height, 8 * channels);

	uchar* ps;
	uchar* pimg = (uchar*)cImage.GetBits(); //获取CImage的像素存贮区的指针
	int step = cImage.GetPitch();//每行的字节数,注意这个返回值有正有负

	// 如果是1个通道的图像(灰度图像) DIB格式才需要对调色板设置  
	// CImage中内置了调色板，我们要对他进行赋值：
	if (1 == channels)
	{
		RGBQUAD* ColorTable;
		int MaxColors = 256;
		//这里可以通过CI.GetMaxColorTableEntries()得到大小(如果你是CI.Load读入图像的话)  
		ColorTable = new RGBQUAD[MaxColors];
		cImage.GetColorTable(0, MaxColors, ColorTable);//这里是取得指针  
		for (int i = 0; i < MaxColors; i++)
		{
			ColorTable[i].rgbBlue = (BYTE)i;
			//BYTE和uchar一回事，但MFC中都用它  
			ColorTable[i].rgbGreen = (BYTE)i;
			ColorTable[i].rgbRed = (BYTE)i;
		}
		cImage.SetColorTable(0, MaxColors, ColorTable);
		delete[]ColorTable;
	}

	//通过指针将Mat的像素值传给CImage
	for (int i = 0; i < height; i++)
	{
		ps = mat.ptr<uchar>(i);
		for (int j = 0; j < width; j++)
		{
			if (1 == channels)
			{
				*(pimg + i*step + j) = ps[j];
				//*(pimg + i*step + j) = 105;
			}
			else if (3 == channels)
			{
				*(pimg + i*step + j * 3) = ps[j * 3];
				*(pimg + i*step + j * 3 + 1) = ps[j * 3 + 1];
				*(pimg + i*step + j * 3 + 2) = ps[j * 3 + 2];
			}
		}
	}
}