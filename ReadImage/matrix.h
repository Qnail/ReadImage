#include <iostream>
#include "malloc.h"
#include "math.h"


class ImageMatrix
{
public:
	ImageMatrix(){};
	ImageMatrix(int, int);
	//void Init(int ,int );

	void putVal(int , int , double);
	double getVal(int, int);

	//���
	ImageMatrix* dotMul(ImageMatrix);

	//������
	ImageMatrix* intMul(double);

	//������
	ImageMatrix* intDiv(double, int);

	//����
	ImageMatrix* intMinus(double);

	//����
	ImageMatrix* intPlus(double);
	////arctan
	//ImageMatrix arctan();

	//�������
	ImageMatrix* matrixMinues(ImageMatrix);
	//�������
	ImageMatrix* matrixPlus(ImageMatrix);

	//�������
	ImageMatrix* matrixDiv(ImageMatrix);

	//�������
	ImageMatrix* matrixMul(ImageMatrix);

	//����ƽ��
	ImageMatrix* matrixsqrt();

	//ȡ��row_start�� ��row_end�� ���row_add ��
	//ImageMatrix selectRow(int row_start,int row_end,int row_add);
	//ImageMatrix selectCol(int col_start, int col_end, int col_add);

	//����ѡ��
	ImageMatrix* select(int num);

	//��������������ĺ�
	double sum();


	void printMatrix();

	//���ز�����


	//copy function
	void copy(ImageMatrix *img)
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				img->arr[i][j] = arr[i][j];
			}
		}
	}

	~ImageMatrix()
	{
		//for (int i = 0; i<height; i++)
		//	free(arr[i]);   //freeһά
		//free(arr);  //free��ά��
	}

private:
	double ** arr;
	//ImageMatrix *s = NULL;
	int height;
	int width;
};