#include "stdafx.h"
#include"Enemy.h"
#include"MyPlane.h"
#include<atlimage.h>

void transparent(CImage &img)  //将图片中白色部分转为透明
{
	for (int i = 0; i < img.GetWidth(); i++)
	{
		for (int j = 0; j < img.GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char *>(img.GetPixelAddress(i, j));
			pucColor[0] = (pucColor[0] * pucColor[3] + 127) / 255;
			pucColor[1] = (pucColor[1] * pucColor[3] + 127) / 255;
			pucColor[2] = (pucColor[2] * pucColor[3] + 127) / 255;
		}
	}
}

void MyPlane::initImage() {
	if (image.Load(_T("..\\Image\\MyPlane.png")) != S_OK)
		AfxMessageBox(_T("Error in loading MyPlane picture"));
	//image.Load(_T("..\\Image\\MyPlane.png"));
	transparent(image);
}

void Enemy::initImage() {
	if (image.Load(_T("..\\Image\\Enemy.png")) != S_OK)
		AfxMessageBox(_T("Error in loading Enemy picture"));
	//image.Load(_T("..\\Image\\Enemy.png"));
	transparent(image);
}

CImage Enemy::image;
