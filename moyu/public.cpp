//-----public.cpp----
//һЩȫ�ֱ����ͺ�����ʵ��

#include "stdafx.h"
#include "public.h"


//��ʼ��ȫ�ֱ���
int CPublic::winShowType = 1;



void CPublic::ShowMat(cv::Mat vMat, HWND hDlg, int vIDC)
{
	if (vMat.empty()) {
		return;
	}

	//��ȡͼƬ�Ŀ� �߶�
	int tImgWidth = vMat.cols;
	int tImgHeight = vMat.rows;
	//��ȡPicture Control�ؼ��Ĵ�С
	CRect rect;
	GetClientRect(GetDlgItem(hDlg,vIDC),&rect);

	//���ͻ���ѡ�е��ؼ���ʾ�ľ���������
	//ScreenToClient(&rect);

	CString msg;
	msg.Format(_T("tImgWidth=%d,tImgHeight=%d, rect��w=%d, h=%d"), tImgWidth, tImgHeight, rect.Width(), rect.Height());
	//MessageBox(msg, _T("showMat"), MB_OK); 

	int tNewWidth, tNewHeight;

	int tLeft = 0, tTop = 0, tRight = rect.Width(), tBottom = rect.Height();
	if (tImgWidth > tImgHeight) {
		//���ͼ���Ǻ��
		tNewWidth = tRight;
		tNewHeight = tNewWidth * tImgHeight / tImgWidth;
		tTop = (tNewWidth - tNewHeight) / 2;
		tBottom = rect.Height() - tTop;
	}
	else {
		//���ͼ��������
		tNewHeight = tBottom;
		tNewWidth = tNewHeight * tImgWidth / tImgHeight;
		tLeft = (tNewHeight - tNewWidth) / 2;
		tRight = rect.Width() - tLeft;
	}

	cv::Mat zoomImg;
	cv::resize(vMat, zoomImg, cv::Size(tNewWidth - 1, tNewHeight - 1));

	//��opencv��ͼתΪCImage,������ʾ��ͼ��ؼ���
	CImage cimg;
	MatToCImage(zoomImg, cimg);

	msg.Format(_T("neww=%d, newh=%d"), cimg.GetWidth(), cimg.GetHeight());
	//MessageBox(msg, _T("mm"), MB_OK); 

	///-----------------------------------------------------------------
	//��������ʾ
	CWnd *pWnd = NULL;
	pWnd->FromHandle(GetDlgItem(hDlg, vIDC));//��ȡ�ؼ���� 

	CDC *pDc = NULL;
	pDc = pWnd->GetDC();//��ȡpicture��DC

						//��ɫ�������,�����߿�
	CBrush brush(RGB(255, 255, 255));

	CRect tRect = CRect(1, 1, rect.Width() - 2, rect.Height() - 2);
	pDc->FillRect(tRect, &brush);
	cimg.Draw(pDc->m_hDC, CRect(tLeft + 1, tTop + 1, tRight - 1, tBottom - 1));

	ReleaseDC();
	//msg.Format(_T("tLeft=%d,tTop=%d, tRight=%d,tBottom=%d"), tLeft, tTop, tRight, tBottom);
	//MessageBox(msg, _T("showMat"), MB_OK);
}


void CPublic::MatToCImage(cv::Mat& mat, CImage& cImage)
{
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	cImage.Destroy();//��һ���Ƿ�ֹ�ظ���������ڴ�����
	cImage.Create(width, height, 8 * channels);

	uchar* ps;
	uchar* pimg = (uchar*)cImage.GetBits(); //��ȡCImage�����ش�������ָ��
	int step = cImage.GetPitch();//ÿ�е��ֽ���,ע���������ֵ�����и�

	// �����1��ͨ����ͼ��(�Ҷ�ͼ��) DIB��ʽ����Ҫ�Ե�ɫ������  
	// CImage�������˵�ɫ�壬����Ҫ�������и�ֵ��
	if (1 == channels)
	{
		RGBQUAD* ColorTable;
		int MaxColors = 256;
		//�������ͨ��CI.GetMaxColorTableEntries()�õ���С(�������CI.Load����ͼ��Ļ�)  
		ColorTable = new RGBQUAD[MaxColors];
		cImage.GetColorTable(0, MaxColors, ColorTable);//������ȡ��ָ��  
		for (int i = 0; i < MaxColors; i++)
		{
			ColorTable[i].rgbBlue = (BYTE)i;
			//BYTE��ucharһ���£���MFC�ж�����  
			ColorTable[i].rgbGreen = (BYTE)i;
			ColorTable[i].rgbRed = (BYTE)i;
		}
		cImage.SetColorTable(0, MaxColors, ColorTable);
		delete[]ColorTable;
	}

	//ͨ��ָ�뽫Mat������ֵ����CImage
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