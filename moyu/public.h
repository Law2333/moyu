//----public.h----
//全局公用类的声明，全局变量和函数

#pragma once


//全局公用类
class CPublic
{
public:

	CPublic();
	virtual ~CPublic();

public:
	//全局变量,菜单栏控制图片显示模式
	static int  winShowType; 
	//全局函数，Mat类转为CImage类
	static void MatToCImage(cv::Mat& mat, CImage& cImage); 
	//Mat图像显示到指定的pic控件
	static void ShowMat(cv::Mat vMat, HWND hDlg, int vIDC);
};

