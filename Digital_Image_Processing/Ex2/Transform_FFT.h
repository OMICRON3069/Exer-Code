#include <math.h>
#define TPI 3.1415926
struct ComplexNumber
{
	double imag;//�鲿
	double real;//ʵ��
};
public class Transform_FFT
{
    public:
	double ** m_pImgData;      //����ͼ��
	double ** m_pImgDataOut; //���ͼ��
	int width, height, m_imgWidthOut, m_imgHeightOut; //�������ͼ��ĸ߿�	
	//����ͼ���2���ݴη���ʱ����չͼ��Ļ�����ָ��
	double ** m_pImgExpandBuf;
      ComplexNumber ** m_pFFTBuf; //����Ҷ�任������
	bool m_isExpanded; //ͼ���Ƿ���չ�ı�־����
	Transform_FFT(double ** m_pImgData,int width, int height); //���캯��	
	~Transform_FFT(); //��������	
	void Fourier(); //ͼ����Ҷ�任
	void IFourier(); //����Ҷ���任
	void FourierEx(int *,int *); //��չ�ĸ���Ҷ�任	
	void IFourierEx(double **); //��չ�ĸ���Ҷ���任  	
	void FFT1D(ComplexNumber *arrayBuf, int n); //һάFFT���任	
	void IFFT1D(ComplexNumber *arrayBuf, int n); //һάIFFT���任
	//��άFFT�任
	void ImgFFT2D(double ** imgBuf, int thiswidth, int thisheight, double ** imgBufOut);
	//��άFFT���任
	void ImgIFFT2D(double ** imgBufOut, int thiswidth, int thisheight);

	void D(double K, double ** a);   //Dת��
	void IdealLowFilter(unsigned char ** d_proImage,int R);
};

