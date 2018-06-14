#include "StdAfx.h"
#include "Transform_FFT.h"
#include <stdlib.h>
#include <string>  
//���캯��
Transform_FFT::Transform_FFT(double ** m_pImgData,int width, int height)
{
	this->m_pImgData = m_pImgData; /*��ʼ������ͼ��*/
	m_pImgDataOut = NULL;	/*��ʼ�����ͼ��*/
	this->width = width;	/*��ʼ��������*/
	this->height = height;	/*��ʼ������߶�*/
	m_imgWidthOut = 0 ;		/*��ʼ��������*/
	m_imgHeightOut = 0;		/*��ʼ������߶�*/
	m_pFFTBuf = NULL;		/*����Ҷ�任������Ϊ��*/
	m_pImgExpandBuf = NULL;		/*����ͼ����չ������ָ���ʼ��Ϊ0*/
	m_isExpanded = false;		/*ͼ����չ��ʶΪ��*/
}
Transform_FFT::~Transform_FFT( )  //��������
	{   //�ͷ����ͼ�񻺳���
	if (m_pImgDataOut != NULL)
	{          for (int a = 0; a < m_imgHeightOut; a++)
			delete [] m_pImgDataOut[a];
		delete []m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	//�ͷŸ���Ҷ�任������
	if (m_pFFTBuf != NULL)
	{          for (int a = 0; a < m_imgHeightOut; a++)
			delete [] m_pFFTBuf[a];
		delete []m_pFFTBuf;
		m_pFFTBuf = NULL;
	}
	//���ͼ����չ���ͷ�ͼ����չ������
	if (m_isExpanded == false)
	{           for (int a = 0; a < m_imgHeightOut; a++)
			delete [] m_pImgExpandBuf[a];
		delete [] m_pImgExpandBuf;
		m_pImgExpandBuf = NULL;
	}
}
void Transform_FFT::FFT1D(ComplexNumber *arrayBuf, int n)
/*�Ը����ṹ������arrayBuf ����һάFFT���任�����Դ��arrayBuf��*/
{    
	int i,k,r;	
	ComplexNumber *buf1 = new ComplexNumber[n]; //���볤��n����������buf1
	memcpy(buf1,arrayBuf,sizeof(ComplexNumber)*n);  //��arrayBuf������buf1
	ComplexNumber *buf2 = new ComplexNumber[n];  //���볤��n����������buf2
	//��arrayBuf����Ԫ�ػ�2��ȡ�����ţ� 0��1��2��3��4��5��6��7  �˵����жԵ����Ϊ  0��4��2��6��1��5��3��7
	int t1,t2;
	for (r = 1;  pow(2.0,r) < n;  r++)
	{           t1= (int)pow(2.0, r);
		t2 =(int)pow(2.0,r-1);
		for (k = 0; k < t1; k++)
		{                for (i = 0; i < n/t1; i++)
			{buf2[k*n/t1+i].real = buf1[k/2*n/t2+i*2+k%2].real;
			  buf2[k*n/t1+i].imag = buf1[k/2*n/t2+i*2+k%2].imag; }
		}
		memcpy(buf1,buf2,sizeof(ComplexNumber)*n);
	}
//���õ����㷨����FFT ��buf1��r �������룬buf2��ŵ�r �������
	double c,s;
	for (r=1;pow(2.0,r)<=n;r++)
	{           t1 = (int)pow(2.0,r);
		for (k=0;k<n/t1;k++)
		{        for (i=t1/2;i<t1;i++)
		        {                
		               c = cos(-2*TPI*(i-t1/2)/t1);  //��Ȩ����
		               s = sin(-2*TPI*(i-t1/2)/t1);
		               buf1[k*t1+i].real = buf2[k*t1+i].real*c-buf2[k*t1+i].imag*s;
		               buf1[k*t1+i].imag = buf2[k*t1+i].imag*c+buf2[k*t1+i].real*s;
		         }
		}
		for (k=0;k<n/t1;k++)
		{
		         for (i=0;i<t1/2;i++)
		        {
			buf2[k*t1+i].real = buf1[k*t1+i].real+buf1[k*t1+i+t1/2].real;
			buf2[k*t1+i].imag = buf1[k*t1+i].imag+buf1[k*t1+i+t1/2].imag;
		        }
for (i=t1/2;i<t1;i++)
			{
				buf2[k*t1+i].real = buf1[k*t1+i-t1/2].real-buf1[k*t1+i].real;
				buf2[k*t1+i].imag = buf1[k*t1+i-t1/2].imag-buf1[k*t1+i].imag;
			}
		}
		//��r�����������buf1����Ϊ��һ������������
		memcpy(buf1,buf2,sizeof(ComplexNumber)*n);
	}
	//����Ҷ�任�Ľ������arrayBuf
	memcpy(arrayBuf,buf2,sizeof(ComplexNumber)*n);
	//�ͷŻ�����
	delete []buf2;
	delete []buf1;
}
void Transform_FFT::IFFT1D(ComplexNumber *arrayBuf, int n)
/*�Ը����ṹ������arrayBuf����һάIFFT���任�����Դ��arrayBuf��*/
{
	int i;
	//������arrayBuf����

	for (i=0;i<n;i++)	
		arrayBuf[i].imag = - arrayBuf[i].imag;
	//һά���ٸ���Ҷ�任
	FFT1D(arrayBuf,n);  

	//ʱ���������������N
	for (i=0;i<n;i++)
	{
		arrayBuf[i].real = arrayBuf[i].real/n;
		arrayBuf[i].imag = -arrayBuf[i].imag/n;
	}
}
void Transform_FFT::ImgFFT2D(double **imgBuf, int thiswidth, int thisheight, double **imgBufOut)
{   
	int i, j,u,v;	
	for (i=0;i<thisheight;i++)        //ͼ�����ݱ�ɸ�����ʽ����m_pFFTBuf
	{           for (j = 0;j<thiswidth;j++)
		{                double a  = imgBuf[i][j];
			m_pFFTBuf[i][j].real = a;
			m_pFFTBuf[i][j].imag = 0;
		}
	}	
	ComplexNumber *array = new ComplexNumber[thisheight];	//���볤��Ϊheight
	for (u=0;u<thiswidth;u++) //������һάFFT
	{           for (v=0;v<thisheight;v++)
		{              array[v].real = m_pFFTBuf[v][u].real;
			array[v].imag = m_pFFTBuf[v][u].imag;
		}
FFT1D(array,thisheight);
		for (v=0;v<thisheight;v++)
		{                m_pFFTBuf[v][u].real = array[v].real;
			m_pFFTBuf[v][u].imag = array[v].imag; }		
	}
	delete[] array;
	array = new ComplexNumber [thiswidth];
	//�ٺ���һά���ٸ���Ҷ�任
	for (v=0;v<thisheight;v++)
	{           for (u=0;u<thiswidth;u++)
		{                array[u].real = m_pFFTBuf[v][u].real;
			array[u].imag = m_pFFTBuf[v][u].imag;
		}
		FFT1D(array,thiswidth);
		for (u=0;u<thiswidth;u++)
		{
			m_pFFTBuf[v][u].real = array[u].real;
			m_pFFTBuf[v][u].imag = array[u].imag;
		}
	}
	delete[] array;
//��Ƶ��ͼ���
	double t;

	for (i=0;i<thisheight;i++)
	{
		for (j=0;j<thiswidth;j++)
		{
			t = sqrt(m_pFFTBuf[i][j].real*m_pFFTBuf[i][j].real + m_pFFTBuf[i][j].imag*m_pFFTBuf[i][j].imag);
			t = t/500;
			if (t>255)
			{
				imgBufOut[i][j] = 255;
			} 
			else
			{
				imgBufOut[i][j] = t;
			}
		}
	}
}
void Transform_FFT::ImgIFFT2D(double **imgBufOut, int thiswidth, int thisheight)
{    
	if (!m_pFFTBuf)          return;  //������Ҷ�任������Ϊ�գ���ʧ�ܷ���	
	int  i, u, v;	
	ComplexNumber *array = new ComplexNumber[thisheight];  //������IFFT
	for (u=0;u<thiswidth;u++)
	{           for (v=0; v<thisheight; v++)
		{               array[v].real = m_pFFTBuf[v][u].real;
			array[v].imag = m_pFFTBuf[v][u].imag;
		}
		IFFT1D(array,thisheight);
		for (v=0;v<thisheight;v++)
		{               m_pFFTBuf[v][u].real = array[v].real;
			m_pFFTBuf[v][u].imag = array[v].imag;
		}
	}
	delete[] array;
	
     array = new ComplexNumber [thiswidth]; 	
//�ٺ�����Ҷ���任
	for (v=0;v<thisheight;v++)
	{
		for (u=0;u<thiswidth;u++)
		{
			array[u].real = m_pFFTBuf[v][u].real;
			array[u].imag = m_pFFTBuf[v][u].imag;
		}
		IFFT1D(array,thiswidth);
		for (u=0;u<thiswidth;u++)
		{
			m_pFFTBuf[v][u].real = array[u].real;
			m_pFFTBuf[v][u].imag = array[u].imag;
		}
	}
	delete []array;
//��m_pFFTBuf�ķ����ף��ָ�ͼ�����imgBufOut
	double t;
	for (i=0; i<thisheight;i++)
	{
		for (int j = 0; j<thiswidth;j++)
		{
			t = sqrt(m_pFFTBuf[i][j].real*m_pFFTBuf[i][j].real + m_pFFTBuf[i][j].imag*m_pFFTBuf[i][j].imag);
			
                                 if (t>255)
			          imgBufOut[i][j] = 255;			
			else
			          imgBufOut[i][j] = t;
			
		}
	 }
}
void Transform_FFT::Fourier()
/*������ͼ����п��ٸ���Ҷ�任��Ҫ������ͼ��Ŀ�͸߱�����2���ݴη�*/
{
	//���ͼ��Ĵ�С������ͼ��Ĵ�С��ͬ
	m_imgWidthOut = width;
	m_imgHeightOut = height;

	//���븵��Ҷ�任������������ʼ��Ϊ0
	m_pFFTBuf = new ComplexNumber*[m_imgHeightOut];
	for (int a = 0; a<m_imgHeightOut; a++)
	{
		m_pFFTBuf[a] = new ComplexNumber [m_imgWidthOut]; 
	}

	//����ͼ�����ݽ��ж�ά����Ҷ�任
	ImgFFT2D(m_pImgData,m_imgWidthOut,m_imgHeightOut,m_pImgDataOut);
}
void Transform_FFT::IFourier()
/*����ͼ��Ŀ��ٸ���Ҷ���任����ImgFFT()�ɶ�ʹ��*/
{
	//ͼ��Ķ�ά����Ҷ���任���任�������m_pImgDataOut
	ImgIFFT2D(m_pImgDataOut,m_imgWidthOut,m_imgHeightOut);
}
void Transform_FFT::FourierEx(int *d_height,int* d_width)
/*ͼ�񳤺Ϳ���2���ݴη���ֱ����ImgFFT()����������ͼ��ĳ��Ϳ������չ�󣬽���FFT*/
{   //�ж�����ͼ��ĳ��Ϳ��Ƿ���2���ݴη�������isPowerOf2��1������isPowerOf2��0
	int  isPOwerOf2 = 1;
	int i = 1;
	while (i<width)
	{
		i *= 2;
	}
	if ( i != width)//����2���ݴη�
	{
		isPOwerOf2 = 0;
	}
	i =1;
	while (i<height)
	{
		i = i*2;
	}
	if (i != height)//�߲���2���ݴη�
	{           isPOwerOf2 = 0;
	}
//����ͼ��ĳ��Ϳ���2���ݴη�������Ҫ��չ��ֱ�ӵ���ImgFFT()��������
	if (isPOwerOf2)
	{           Fourier();
	} 
	else
	{           //����ͼ��ĳ������2���ݴη�����ͼ������չ
		int i = 1;
		while (i<width)
		{
			i *= 2;
		}
		m_imgWidthOut = i;

		i =1;
		while (i<height)
		{
			i = i*2;
		}
		m_imgHeightOut = i;

		*d_height = m_imgHeightOut;
		*d_width = m_imgWidthOut;
//������չ������m_pImgExpandBuf
		m_pImgExpandBuf = new double*[m_imgHeightOut];
		for (int a = 0; a<m_imgHeightOut; a++)
			m_pImgExpandBuf[a] = new double [m_imgWidthOut]; 
		
		//m_pImgExpandBuf��������0
		for (int m=0;m<m_imgHeightOut;m++)
		{
			for (int n=0;n<m_imgWidthOut;n++)
			         m_pImgExpandBuf[m][n] =0; 
			
		}
		//����ͼ�����ݿ�����m_pImgExpandBuf�����½ǲ��֣�����Ϊ0
		for (int m=0;m<height;m++)
		{
			for (int n=0;n<width;n++)
			
			       m_pImgExpandBuf[m+m_imgHeightOut-height][n] =m_pImgData[m][n]*pow((-1.0),(m+n)); 
			
		}
//�������ͼ�񻺳���������ʼ��Ϊ0
		m_pImgDataOut = new double*[m_imgHeightOut];
		for (int a = 0; a<m_imgHeightOut; a++)
		                m_pImgDataOut[a] = new double [m_imgWidthOut]; 
		
		for (int m=0;m<m_imgHeightOut;m++)
		{                for (int n=0;n<m_imgWidthOut;n++)
			         m_pImgDataOut[m][n] =0; 
			
		}
		//���븵��Ҷ������������ʼ��Ϊ0
		m_pFFTBuf = new ComplexNumber*[m_imgHeightOut];
		for (int a = 0; a<m_imgHeightOut; a++)
		
			m_pFFTBuf[a] = new ComplexNumber [m_imgWidthOut]; 
		
		//��չ������ݽ��ж�άFFT
		ImgFFT2D(m_pImgExpandBuf, m_imgWidthOut, m_imgHeightOut, m_pImgDataOut);
		//ͼ����չ��ʶ������1
		m_isExpanded = true;

	}
}
void Transform_FFT::IFourierEx(double **d_proImg)
/*����ͼ����չ��Ŀ��ٸ���Ҷ���任����ImgFFTEx( )�ɶԵ���*/
{
	//ͼ��Ķ�άIFFT���任�������m_pImgDataOut
	ImgIFFT2D(m_pImgDataOut,m_imgWidthOut,m_imgHeightOut);
    
	//��m_pImgDataOut��ͼ�����ݿ�����
	for (int i=0;i<m_imgHeightOut;i++)
	{
		for (int j=0;j<m_imgWidthOut;j++)
		{
			d_proImg[i][j] = m_pImgDataOut[i][j];
		}
	}
}
void Transform_FFT::D(double K,double ** d_proImag)
/*   D = ln(1+K|F(u,v)|)  ����proImage[u][v] = log(1+K*proImage[u][v])
	KΪ������ͨ��ȡֵΪ[1,10],���Ե�����ʾ�����ֵ����Сֵ */
{
	int u,v;
	for(u=0;u<m_imgHeightOut;u++)
	{
		for(v=0;v<m_imgWidthOut;v++)
		{
			m_pImgDataOut[u][v] = log(1+K*m_pImgDataOut[u][v]);
		}
	}
	for (int i=0;i<m_imgHeightOut;i++)
	{
		for (int j=0;j<m_imgWidthOut;j++)
		{
			d_proImag[i][j] = m_pImgDataOut[i][j];
		}
	}

}
void Transform_FFT::IdealLowFilter(unsigned char ** d_proImage,int R){
	int u,v;
	double d;
	for(u = 0;v<m_imgHeightOut;u++)
	{

		for(v = 0;v < m_imgWidthOut;v++)
		{
			d = sqrt(pow((double)(u-m_imgHeightOut/2),2.0)+pow((double)(v-m_imgWidthOut/2),2.0));
			if(d>R)
			{
				m_pImgDataOut[u][v] = 0;
				m_pFFTBuf[u][v].real= 0;
				m_pFFTBuf[u][v].imag = 0;
			}
			
			
		}
for(int i =0;i<height;i++)
		{

			for(int j=0;j<width;j++)
			{

				d_proImage[i][j] = (int)(m_pImgDataOut[i + (m_imgHeightOut-height)/2][j + (m_imgWidthOut-width)/2]*20);
				if(d_proImage[i][j]>255)
					d_proImage[i][j] = 255;

			}
		}
	}
}


