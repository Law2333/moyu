//----public.h----
//ȫ�ֹ������������ȫ�ֱ����ͺ���

#pragma once


//ȫ�ֹ�����
class CPublic
{
public:

	CPublic();
	virtual ~CPublic();

public:
	//ȫ�ֱ���,�˵�������ͼƬ��ʾģʽ
	static int  winShowType; 
	//ȫ�ֺ�����Mat��תΪCImage��
	static void MatToCImage(cv::Mat& mat, CImage& cImage); 
	//Matͼ����ʾ��ָ����pic�ؼ�
	static void ShowMat(cv::Mat vMat, HWND hDlg, int vIDC);
};

