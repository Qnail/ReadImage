#include <stdio.h>
#include "BitmapRot.h"
#include "stdlib.h"
#include "math.h"
#include <iostream>
#include "matrix.h"

#define PI 3.1416//Բ���ʺ궨��
#define LENGTH_NAME_BMP 30//bmpͼƬ�ļ�������󳤶�

#define MIN_ZERO 0.0000000000022204

using namespace std;
//��������
BITMAPFILEHEADER strHead;
RGBQUAD strPla[256];//256ɫ��ɫ��
BITMAPINFOHEADER strInfo;



int main(){
	//================================================��ͼƬ=============================================
	char strFile[LENGTH_NAME_BMP];//bmp�ļ���
	IMAGEDATA *imagedata = NULL;//��̬����洢ԭͼƬ��������Ϣ�Ķ�ά����
	IMAGEDATA *u_result = NULL;//��̬����洢���ͼƬ��������Ϣ�Ķ�ά����

	ImageMatrix imageArr;

	int width, height;//ͼƬ�Ŀ�Ⱥ͸߶�
	cout << "��������Ҫ��ȡ���ļ���:" << endl;
	cin >> strFile;
	FILE *fpi, *fpw;
	fpi = fopen(strFile, "rb");
	if (fpi != NULL){
		//�ȶ�ȡ�ļ�����
		WORD bfType;
		fread(&bfType, 1, sizeof(WORD), fpi);
		if (0x4d42 != bfType)
		{
			cout << "the file is not a bmp file!" << endl;
			return NULL;
		}
		//��ȡbmp�ļ����ļ�ͷ����Ϣͷ
		fread(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpi);
		//showBmpHead(strHead);//��ʾ�ļ�ͷ
		fread(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpi);
		//showBmpInforHead(strInfo);//��ʾ�ļ���Ϣͷ

		//��ȡ��ɫ��
		for (unsigned int nCounti = 0; nCounti < strInfo.biClrUsed; nCounti++)
		{
			fread((char *)&(strPla[nCounti].rgbBlue), 1, sizeof(BYTE), fpi);
			fread((char *)&(strPla[nCounti].rgbGreen), 1, sizeof(BYTE), fpi);
			fread((char *)&(strPla[nCounti].rgbRed), 1, sizeof(BYTE), fpi);
			fread((char *)&(strPla[nCounti].rgbReserved), 1, sizeof(BYTE), fpi);
		}

		width = strInfo.biWidth;
		height = strInfo.biHeight;
		//ͼ��ÿһ�е��ֽ���������4��������
		//width = (width * sizeof(IMAGEDATA) + 3) / 4 * 4;
		imagedata = (IMAGEDATA*)malloc(width * height * sizeof(IMAGEDATA));
		//imagedata = (IMAGEDATA*)malloc(width * height);

		//���ͼ�����
		u_result = (IMAGEDATA*)malloc(width * height*sizeof(IMAGEDATA));

		//��ʼ��ͼƬ����
		imageArr = ImageMatrix(height, width);

		//��ʼ��ԭʼͼƬ����������
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				(*(imagedata + i * width + j)).blue = 0;
				(*(imagedata + i * width + j)).green = 0;
				(*(imagedata + i * width + j)).red = 0;

			}
		}
		//��ʼ�����ͼƬ����������
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				(*(u_result + i * width + j)).blue = 0;
				(*(u_result + i * width + j)).green = 0;
				(*(u_result + i * width + j)).red = 0;
			}
		}
		//fseek(fpi,54,SEEK_SET);
		//����ͼƬ����������
		fread(imagedata, sizeof(struct tagIMAGEDATA) * width, height, fpi);
		fclose(fpi);
	}
	else
	{
		cout << "file open error!" << endl;
		return NULL;
	}
	//============================================��ͼ����=====================================




	//============================================�ҶȻ�ͼƬ=====================================
	//R*0.299 + G*0.587 + B*0.114

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			BYTE gray = int((*(imagedata + i * width + j)).red)*0.299 + int((*(imagedata + i * width + j)).green)*0.587 + int((*(imagedata + i * width + j)).blue)*0.114;
			(*(imagedata + i * width + j)).blue = gray;
			(*(imagedata + i * width + j)).green = gray;
			(*(imagedata + i * width + j)).red = gray;
			imageArr.putVal(height-1-i, j, double(gray));
		}
	}

	//imageArr.printMatrix();


	////============================================��ʼ������=====================================
	int xc = height / 2;
	int yc = width / 2;
	int tem = 0;
	double r = xc / 3.0;
	////ͼƬȦ����ҶȺ�
	//int sum_in = 0;
	//int sum_out = 0;
	////ͼƬȦ����������
	//int count_in = 0;
	//int count_out = 0;
	////����
	//int on = 0;
	//for (int i = 0; i < height; ++i)
	//{
	//	for (int j = 0; j < width; ++j)
	//	{
	//		tem = ((j - xc)*(j - xc) + (i - yc)*(i - yc));
	//		if ((r*r - r + 1) <= tem&&tem <= (r*r + r - 1))
	//		{
	//			(*(imagedata + i * width + j)).blue = 0;
	//			(*(imagedata + i * width + j)).green = 0;
	//			(*(imagedata + i * width + j)).red = 255;
	//			on++;
	//		}
	//		//��
	//		if ((r*r - r + 1) > tem)
	//		{
	//			sum_in += (*(imagedata + i * width + j)).blue;
	//			count_in++;
	//		}
	//		//��
	//		if (tem > (r*r + r - 1))
	//		{
	//			sum_out += (*(imagedata + i * width + j)).blue;
	//			count_out++;
	//		}
	//	}
	//}
	////cout << count_in + count_out + on << " " << width*height << endl;
	//
	//float c1 = sum_in / count_in;
	//float c2 = sum_out / count_out;

	//==========================================����
	
	ImageMatrix* u = new ImageMatrix(height, width);
	



	for (int i = 1; i <= height; ++i)
	{
		for (int j = 1; j <= width; ++j)
		{
			u->putVal(i-1, j-1, (r - sqrt((i - xc)*(i - xc) + (j - yc)*(j - yc))));
		}
	}

	//u->printMatrix();



	
	ImageMatrix *C = new ImageMatrix(height, width);
	//C.Init(height, width);
	ImageMatrix *m = new ImageMatrix(height, width);
	//m.Init(height, width);
	ImageMatrix *C1 = new ImageMatrix(height, width);
	//C1.Init(height, width);
	ImageMatrix *C2 = new ImageMatrix(height, width);
	//C2.Init(height, width);
	ImageMatrix *C3 = new ImageMatrix(height, width);
	//C3.Init(height, width);
	ImageMatrix *C4 = new ImageMatrix(height, width);
	//C4.Init(height, width);
	ImageMatrix *Hu = new ImageMatrix(height, width);
	//Hu.Init(height, width);
	ImageMatrix *del_H = new ImageMatrix(height, width);
	//del_H.Init(height, width);



	double epsilon = 1.0;
	int num = 2500;
	double delta_t = 0.1;

	ImageMatrix *temp0 = new ImageMatrix(height, width);
	ImageMatrix *temp1 = new ImageMatrix(height, width);
	ImageMatrix *temp2 = new ImageMatrix(height, width);
	ImageMatrix *temp3 = new ImageMatrix(height, width);
	ImageMatrix *temp4 = new ImageMatrix(height, width);
	//=====================================/////////////////////////////////////////////////////////////////////////////
	for (int ii = 0; ii < 1;ii++)
	{
		//std::cout << ii << std::endl;
		
		//0.5*(1+(2/pi)*atan(u/epsilon));
		//����Hu

		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				Hu->putVal(i, j, (0.5*(1 + (2 / PI)*atan(u->getVal(i, j)/epsilon))));
			}
		}


		//Hu->printMatrix();
		//����c1 c2
		Hu->copy(temp0);
		Hu->copy(temp1);
		//double imt = (temp->dotMul(imageArr))->sum();
		double c1 = (temp0->dotMul(imageArr))->sum() / temp1->sum();
		Hu->copy(temp0);
		Hu->copy(temp1);
		double c2 = temp0->intMinus(1.0)->dotMul(imageArr)->sum() / temp1->intMinus(1.0)->sum();



		//(1/pi)*epsilon./(epsilon^2+u.^2);
		u->copy(temp0);
		(temp0->dotMul(*u)->intPlus(epsilon*epsilon)->intDiv(1 / PI*epsilon, 1))->copy(del_H);

		//del_H->printMatrix();

		del_H->copy(temp0);
		temp0->intMul(delta_t)->copy(m);
		//m->printMatrix();

		//1./sqrt();
		//eps+(u(:,[2:y_center,y_center])-u).^2+0.25*(u([2:x_center,x_center],:)-u([1,1:x_center-1],:)).^2
		
		u->copy(temp0);
		u->copy(temp1);
		u->copy(temp2);
		//(u.select(1).matrixMinues(u).matrixMul(u.select(1).matrixMinues(u)))
		temp0->printMatrix();
		temp0->select(1)->matrixMinues(*u);
		temp0->matrixMul(*temp0);
		//temp0->printMatrix();
		//(u.select(3).matrixMinues(u.select(4)).matrixMul(u.select(3).matrixMinues(u.select(4))))
		temp1->select(3)->matrixMinues(*(temp2->select(4)));
		temp1->matrixMul(*temp1);

		(((temp0->matrixPlus(*(temp1->intMul(0.25))))->intPlus(MIN_ZERO))->matrixsqrt()->intDiv(1, 1))->copy(C1);
		C1->printMatrix();
		//u.printMatrix();
		//u.select(1).printMatrix();

		//1./sqrt(eps+(u-u(:,[1,1:y_center-1])).^2+0.25*(u([2:x_center,x_center],[1,1:y_center-1])-u([1,1:x_center-1],[1,1:y_center-1])).^2);
		u->copy(temp0);
		u->copy(temp1);
		u->copy(temp2);
		//(u.matrixMinues(u.select(2))).matrixMul(u.matrixMinues(u.select(2)))
		temp0->matrixMinues(*(temp1->select(2)));
		temp0->matrixMul(*(temp0));
		//(u.select(3).select(2).matrixMinues(u.select(4).select(2)))
		temp1->select(3)->select(2)->matrixMinues(*(temp2->select(4)->select(2)));
		temp1->matrixMul(*temp1);

		(((temp0->matrixPlus(*(temp1->intMul(0.25))))->intPlus(MIN_ZERO))->matrixsqrt()->intDiv(1, 1))->copy(C2);
		//C2.printMatrix();

		//C_3=1./sqrt(eps+(u([2:x_center,x_center],:)-u).^2+0.25*(u(:,[2:y_center,y_center])-u(:,[1,1:y_center-1])).^2);
		u->copy(temp0);
		u->copy(temp1);
		u->copy(temp2);
		//((u.select(3).matrixMinues(u)).matrixMul(u.select(3).matrixMinues(u)))
		temp0->select(3)->matrixMinues(*u);
		temp0->matrixMul(*temp0);

		//(u.select(1).matrixMinues(u.select(3)))
		temp1->select(1)->matrixMinues(*(temp2->select(3)));
		temp1->matrixMul(*(temp1));

		(((temp0->matrixPlus(*(temp1->intMul(0.25))))->intPlus(MIN_ZERO))->matrixsqrt()->intDiv(1, 1))->copy(C3);
		//C3.printMatrix();


		//C_4 = 1. / sqrt(eps + (u - u([1, 1:x_center - 1], :)). ^ 2 + 0.25*(u([1, 1:x_center - 1], [2:y_center, y_center]) - u([1, 1:x_center - 1], [1, 1:y_center - 1])). ^ 2);

		//
		u->copy(temp0);
		u->copy(temp1);
		u->copy(temp2);
		u->copy(temp3);
		//((u.matrixMinues(u.select(4))).matrixMul(u.matrixMinues(u.select(4))))
		temp0->matrixMinues(*(temp1->select(4)));
		temp0->matrixMul(*(temp0));
		//(u.select(4).select(1).matrixMinues(u.select(4).select(2)))
		temp2->select(4)->select(1)->matrixMinues(*(temp3->select(4)->select(2)));
		temp2->matrixMul(*temp2);

		(((temp0->matrixPlus(*(temp2->intMul(0.25))))->intPlus(MIN_ZERO))->matrixsqrt()->intDiv(1, 1))->copy(C4);
		//C4.printMatrix();
		//C=1+nu*m.*(C_1+C_2+C_3+C_4);
		m->copy(temp0);
		C1->copy(temp1);

		((temp0->intMul(num)->dotMul(*(temp1->matrixPlus(*C2)->matrixPlus(*C3)->matrixPlus(*C4))))->intPlus(1.0))->copy(C);

		
		//update u
		//
		//u=(u+
		//	nu*

		//	m.*(
		//	C_1.*u(:,[2:y_center,y_center])  1
		//	+C_2.*u(:,[1,1:y_center-1])  2
		//	+C_3.*u([2:x_center,x_center],:) 3
		//	+C_4.*u([1,1:x_center-1],:) 4
		//	)

		//	+m.*(
		//	(Img - c2). ^ 2 - (Img - c1). ^ 2
		//	)

		//	). / C;

		u->copy(temp0);
		C1->copy(temp1);
		C2->copy(temp2);
		C3->copy(temp3);
		C4->copy(temp4);
		temp1->dotMul(*(temp0->select(1)));
		u->copy(temp0);
		temp2->dotMul(*(temp0->select(2)));
		u->copy(temp0);
		temp3->dotMul(*(temp0->select(3)));
		u->copy(temp0);
		temp4->dotMul(*(temp0->select(4)));
		u->copy(temp0);
		
		temp0->matrixPlus(*((((temp1->matrixPlus(*(temp2)))->matrixPlus(*(temp3)))->matrixPlus(*(temp4))->dotMul(*m))->intMul(num)));
		m->copy(temp1);

		imageArr.copy(temp2);
		imageArr.copy(temp3);
		//m.dotMul(imageArr.intMinus(c2).matrixMul(imageArr.intMinus(c2)))
		(temp2->intMinus(c2));
		temp2->matrixMul(*temp2);
		temp3->intMul(c2);
		temp3->matrixMul(*temp3);
		
		temp1->dotMul(*(temp2->matrixMul(*temp3)));

		((temp0->matrixPlus(*temp1))->matrixDiv(*C))->copy(u);
		//u.printMatrix();
}



	u->printMatrix();

	//ͨ�����黹ԭͼƬ

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (u->getVal(i, j)>0)
			{
				//��
				if (j == 0){
					//����
					if (i == 0)
					{
						if ((u->getVal(i, j + 1) <= 0) || u->getVal(i + 1, j) <= 0)
						{
							(*(imagedata + (height - 1 - i) * width + j)).blue = 0;
							(*(imagedata + (height - 1 - i) * width + j)).green = 0;
							(*(imagedata + (height - 1 - i) * width + j)).red = 255;
						}
					}
					else if (i == height - 1)//����
					{
						if (u->getVal(i - 1, j) <= 0 || u->getVal(i, j + 1) <= 0)
						{
							(*(imagedata + (height - 1 - i) * width + j)).blue = 0;
							(*(imagedata + (height - 1 - i) * width + j)).green = 0;
							(*(imagedata + (height - 1 - i) * width + j)).red = 255;
						}
					}
					else//����
					{
						if (u->getVal(i + 1, j) <= 0 || u->getVal(i - 1, j) <= 0 || u->getVal(i, j + 1) <= 0)
						{
							(*(imagedata + (height - 1 - i) * width + j)).blue = 0;
							(*(imagedata + (height - 1 - i) * width + j)).green = 0;
							(*(imagedata + (height - 1 - i) * width + j)).red = 255;
						}
					}
				}
				else if (j==width-1)//��
				{
					//����
					if (i == 0)
					{
						if (u->getVal(i , j-1) <= 0 || u->getVal(i+1, j ) <= 0)
						{
							(*(imagedata + (height - 1 - i) * width + j)).blue = 0;
							(*(imagedata + (height - 1 - i) * width + j)).green = 0;
							(*(imagedata + (height - 1 - i) * width + j)).red = 255;
						}
					}
					else if (i == height - 1)//����
					{
						if (u->getVal(i-1, j) <= 0 || u->getVal(i, j-1) <= 0)
						{
							(*(imagedata + (height - 1 - i) * width + j)).blue = 0;
							(*(imagedata + (height - 1 - i) * width + j)).green = 0;
							(*(imagedata + (height - 1 - i) * width + j)).red = 255;
						}
					}
					else//����
					{
						if (u->getVal(i - 1, j) <= 0 || u->getVal(i, j-1) <= 0 || u->getVal(i+1, j) <= 0)
						{
							(*(imagedata + (height - 1 - i) * width + j)).blue = 0;
							(*(imagedata + (height - 1 - i) * width + j)).green = 0;
							(*(imagedata + (height - 1 - i) * width + j)).red = 255;
						}
					}
					
				}
				else//�м�
				{
					if (i==0)//��
					{
						if (u->getVal(i, j-1) <= 0 || u->getVal(i, j + 1) <= 0 || u->getVal(i + 1, j) <= 0)
						{
							(*(imagedata + (height - 1 - i) * width + j)).blue = 0;
							(*(imagedata + (height - 1 - i) * width + j)).green = 0;
							(*(imagedata + (height - 1 - i) * width + j)).red = 255;
						}
					}
					else if (i==height-1)//��
					{
						if (u->getVal(i, j - 1) <= 0 || u->getVal(i, j + 1) <= 0 || u->getVal(i - 1, j) <= 0)
						{
							(*(imagedata + (height - 1 - i) * width + j)).blue = 0;
							(*(imagedata + (height - 1 - i) * width + j)).green = 0;
							(*(imagedata + (height - 1 - i) * width + j)).red = 255;
						}
					}
					else//��
					{
						if (u->getVal(i, j - 1) <= 0 || u->getVal(i, j + 1) <= 0 || u->getVal(i + 1, j) <= 0 || u->getVal(i - 1, j) <= 0 )
						{
							(*(imagedata + (height - 1 - i) * width + j)).blue = 0;
							(*(imagedata + (height - 1 - i) * width + j)).green = 0;
							(*(imagedata + (height - 1 - i) * width + j)).red = 255;
						}
					}
				}
			}
		}
	}

	//==========================================����bmpͼƬ=========================================
	if ((fpw = fopen("b.bmp", "wb")) == NULL)
	{
		cout << "create the bmp file error!" << endl;
		return NULL;
	}
	WORD bfType_w = 0x4d42;
	fwrite(&bfType_w, 1, sizeof(WORD), fpw);
	//fpw +=2;
	fwrite(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpw);
	strInfo.biWidth =  width;
	strInfo.biHeight =  height;
	fwrite(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpw);
	//�����ɫ������
	for (unsigned int nCounti = 0; nCounti<strInfo.biClrUsed; nCounti++)
	{
		fwrite(&strPla[nCounti].rgbBlue, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbGreen, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbRed, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbReserved, 1, sizeof(BYTE), fpw);
	}
	//������������
	int gray = 0;
	for (int i = 0; i <  height; ++i)
	{
		for (int j = 0; j <  width; ++j)
		{

			fwrite(&((*(imagedata + i * width + j)).blue), 1, sizeof(BYTE), fpw);
			fwrite(&((*(imagedata + i * width + j)).green), 1, sizeof(BYTE), fpw);
			fwrite(&((*(imagedata + i * width + j)).red), 1, sizeof(BYTE), fpw);
		}
	}
	fclose(fpw);
	
	//�ͷ��ڴ�
	delete[] imagedata;
	delete[] u_result;

}