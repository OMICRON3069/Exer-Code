

#pragma once
#include "Transform_FFT.h"
namespace s {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 ժҪ
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
		public:
	    Bitmap^   oriBmap  ;        //ԭͼ����
	    Bitmap^   proBmap;         //����ͼ���

	     int      nWidth;                 //ͼ���
	     int      nHeight;                //ͼ���

	     unsigned char **oriImage;              //ԭͼ�Ҷ�
	     unsigned char **proImage;             //�����Ҷ�
	     unsigned char *** oriRGBImage;   //ԭ��ɫͼ��
	private: System::Windows::Forms::GroupBox^  groupBox1;
	public: 
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::ToolStripMenuItem^  invIdealFilterToolStripMenuItem;
			 unsigned char *** proRGBImage;  //�����ɫͼ��
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �ڴ˴���ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  fourierToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  fFTToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  iFFTToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  filterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  idealFilterToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;

	private:
		/// <summary>
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/*isProImage=1����ȡproBmap�Ҷ�ͼ��isProImage=0����oriBmap�ĻҶ�ͼ*/
private: void oriImageInitial(unsigned int isProImage) {
		for ( int i = 0; i < nHeight; i++ )
		   {            for ( int j = 0; j < nWidth; j++ )
			{//��ûҶ�ͼ�񣬴����oriImage[][]��
			if(isProImage==1)
			oriImage[i][j] = (unsigned char)(proBmap->GetPixel(j,i).R*0.299 + proBmap->GetPixel(j,i).G*0.587 + proBmap->GetPixel(j,i).B*0.114);
			else
			oriImage[i][j] = (unsigned char)(oriBmap->GetPixel(j,i).R*0.299 + oriBmap->GetPixel(j,i).G*0.587 + oriBmap->GetPixel(j,i).B*0.114);

                         if(oriImage[i][j]<0)
			oriImage[i][j] = 0;
			if(oriImage[i][j]>255)
			oriImage[i][j] = 255;
			//���RGBͼ�񣬴����oriRGBImage[][][]��
			oriRGBImage[i][j][0] = (unsigned char)oriBmap->GetPixel(j,i).R;
			oriRGBImage[i][j][1] = (unsigned char)oriBmap->GetPixel(j,i).G;
			oriRGBImage[i][j][2] = (unsigned char)oriBmap->GetPixel(j,i).B;
		
                 	}
		        }
		}
private: void oriImageDelete()	//�ͷ��ڴ�ռ�
		 {
		          if(nHeight>0 && nWidth>0)
		        {
			for ( int i = 0; i < nHeight; i++ )    				               {
			        delete [] oriImage[i];
			        delete [] proImage[i];
			        for (int j = 0; j < nWidth; j++)
			        {
				delete [] oriRGBImage[i][j];
				delete [] proRGBImage[i][j];
	             	         }
				delete [] oriRGBImage[i];
				delete [] proRGBImage[i];
			}
	delete [] oriImage;
				delete [] proImage;
				delete [] oriRGBImage;
				delete [] proRGBImage;
			}

			nHeight=0;
			nWidth=0;
		 }
private: void display_image(unsigned char ** curImage)		//��ʾ�Ҷ�ͼ��
		 {
			for ( int i = 0; i < nHeight; i++ )
			{
				for ( int j = 0; j < nWidth; j++ )
				{
				proBmap->SetPixel(j,i,Color::FromArgb(curImage[i][j],curImage[i][j],curImage[i][j]));
				}
			}
			pictureBox2->Invalidate();
		}


		/// �����֧������ķ��� - ��Ҫ
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fourierToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fFTToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->iFFTToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->filterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->idealFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->invIdealFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->fileToolStripMenuItem, 
				this->fourierToolStripMenuItem, this->filterToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1033, 25);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->openToolStripMenuItem, 
				this->saveToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 21);
			this->fileToolStripMenuItem->Text = L"file";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(106, 22);
			this->openToolStripMenuItem->Text = L"open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(106, 22);
			this->saveToolStripMenuItem->Text = L"save";
			// 
			// fourierToolStripMenuItem
			// 
			this->fourierToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fFTToolStripMenuItem, 
				this->iFFTToolStripMenuItem});
			this->fourierToolStripMenuItem->Name = L"fourierToolStripMenuItem";
			this->fourierToolStripMenuItem->Size = System::Drawing::Size(61, 21);
			this->fourierToolStripMenuItem->Text = L"Fourier";
			// 
			// fFTToolStripMenuItem
			// 
			this->fFTToolStripMenuItem->Name = L"fFTToolStripMenuItem";
			this->fFTToolStripMenuItem->Size = System::Drawing::Size(99, 22);
			this->fFTToolStripMenuItem->Text = L"FFT";
			this->fFTToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::fFTToolStripMenuItem_Click);
			// 
			// iFFTToolStripMenuItem
			// 
			this->iFFTToolStripMenuItem->Name = L"iFFTToolStripMenuItem";
			this->iFFTToolStripMenuItem->Size = System::Drawing::Size(99, 22);
			this->iFFTToolStripMenuItem->Text = L"IFFT";
			this->iFFTToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::iFFTToolStripMenuItem_Click);
			// 
			// filterToolStripMenuItem
			// 
			this->filterToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->idealFilterToolStripMenuItem, 
				this->invIdealFilterToolStripMenuItem});
			this->filterToolStripMenuItem->Name = L"filterToolStripMenuItem";
			this->filterToolStripMenuItem->Size = System::Drawing::Size(46, 21);
			this->filterToolStripMenuItem->Text = L"filter";
			// 
			// idealFilterToolStripMenuItem
			// 
			this->idealFilterToolStripMenuItem->Name = L"idealFilterToolStripMenuItem";
			this->idealFilterToolStripMenuItem->Size = System::Drawing::Size(135, 22);
			this->idealFilterToolStripMenuItem->Text = L"Ideal filter";
			this->idealFilterToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::idealFilterToolStripMenuItem_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->Location = System::Drawing::Point(25, 20);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(366, 294);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox2->Location = System::Drawing::Point(24, 20);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(365, 286);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Location = System::Drawing::Point(26, 51);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(429, 324);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"or";
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->pictureBox2);
			this->groupBox2->Location = System::Drawing::Point(546, 51);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(422, 312);
			this->groupBox2->TabIndex = 4;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"po";
			this->groupBox2->Enter += gcnew System::EventHandler(this, &Form1::groupBox2_Enter);
			// 
			// invIdealFilterToolStripMenuItem
			// 
			this->invIdealFilterToolStripMenuItem->Name = L"invIdealFilterToolStripMenuItem";
			this->invIdealFilterToolStripMenuItem->Size = System::Drawing::Size(156, 22);
			this->invIdealFilterToolStripMenuItem->Text = L"InvIdeal filter ";
			this->invIdealFilterToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::invIdealFilterToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1033, 420);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
OpenFileDialog^ openFile1 = gcnew OpenFileDialog ( );
oriImageDelete();		
openFile1->InitialDirectory = "D:\\";
openFile1 ->Filter = "Bitmap Image(*.bmp)|*.bmp";
openFile1 ->RestoreDirectory = true;
		if (openFile1 ->ShowDialog() == Windows::Forms::DialogResult ::OK) 
		{             String^ fileName = openFile1->FileName->ToString();
			oriBmap = gcnew Bitmap (fileName,true);
			proBmap = gcnew Bitmap (fileName,true);
			nWidth  = oriBmap->Width;
			nHeight = oriBmap->Height;
			pictureBox1->Image = oriBmap;
			pictureBox2->Image = proBmap;
			pictureBox1->Refresh();
			pictureBox2->Refresh();	
			if(nHeight>0 && nWidth>0)   //��ͼ��д������oriImage��proImage
		{
		         oriImage = new unsigned char*[nHeight]; //��ʼ��oriImage��proImage
		         proImage = new unsigned char*[nHeight];
		         oriRGBImage = new unsigned char **[nHeight];
		         proRGBImage = new unsigned char **[nHeight];
		         for ( int i = 0; i < nHeight; i++ )
		       {
			oriImage[i] = new unsigned char[nWidth];
			proImage[i] = new unsigned char[nWidth];
			oriRGBImage[i] = new unsigned char *[nWidth];
			proRGBImage[i] = new unsigned char *[nWidth];
			for (int j = 0; j < nWidth; j++)
			{
				oriRGBImage[i][j] = new unsigned char [3];
				proRGBImage[i][j] = new unsigned char [3];
			}
		        }
				oriImageInitial(0);
		}
	} // end if
 SaveFileDialog ^ saveFile1 = gcnew SaveFileDialog();
		saveFile1 -> InitialDirectory = "D:\\imgTest\\";
		saveFile1-> Filter = "Bitmap Image|*.bmp|JPeg Image|*.jpg|Gif Image|*.gif";
		saveFile1 -> Title = "Save an Image File";
		saveFile1 -> ShowDialog ();	
		if ( saveFile1 ->FileName != " ")
		{              switch( saveFile1->FilterIndex )
			{              case 1:
				this->proBmap->Save(saveFile1->FileName ,System::Drawing::Imaging::ImageFormat::Jpeg); 
				break;
				case 2:
				this->proBmap->Save(saveFile1->FileName ,System::Drawing::Imaging::ImageFormat::Bmp); 
				break;
			} //end switch
		} // end if

			 }
private: System::Void fFTToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
 int *m_height = 0,*m_width = 0;
		 int a = 0;
		 int b = 0;
		 m_height = &a;
		 m_width = &b;
		 double ** d_oriImage = new double*[nHeight];
		 for (int i = 0; i<nHeight; i++)
		           d_oriImage[i] = new double [nWidth]; 
		 oriImageInitial(0);
		 for(int i=0;i<nHeight;i++)
		 {         for(int j=0;j<nWidth;j++)
			    d_oriImage[i][j] = oriImage[i][j];
		 }
		 Transform_FFT*  imgFT = new Transform_FFT(d_oriImage,nWidth,nHeight);
		 imgFT->FourierEx(m_height,m_width);//����Ҷ�任��proImage Ƶ���ֵ
	 double ** d_proImage = new double*[a];
		 for (int i = 0; i<a; i++)
		                d_proImage[i] = new double [b];
		
                   imgFT->D(2,d_proImage);			//Dת��
		 for(int i=0;i<nHeight;i++)
		 {
		         for(int j=0;j<nWidth;j++)
		        {
		 proImage[i][j] = (int)(d_proImage[i+(a-nHeight)/2][j+(b-nWidth)/2]*10);
			 if (proImage[i][j] > 255)						                 proImage[i][j] = 255;				
		        }
		 }
		 display_image(proImage);
	  
	
		 }
private: System::Void iFFTToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
 int *m_height = 0,*m_width = 0;
		 int a = 0;
		 int b = 0;
		 m_height = &a;
		 m_width = &b;
		 double ** d_oriImage = new double*[nHeight];
		 for (int i = 0; i<nHeight;i++)
			 d_oriImage[i] = new double [nWidth];
		 oriImageInitial(0);
		 for(int i=0;i<nHeight;i++)
		 {
			 for(int j=0;j<nWidth;j++)
			 {
			        d_oriImage[i][j] = oriImage[i][j];
			 }
		 }
	 Transform_FFT* imgFT = new Transform_FFT(d_oriImage,nWidth,nHeight);

		 imgFT->FourierEx(m_height,m_width);//����Ҷ�任��proImage����Ƶ��ķ���ֵ

		 double ** d_proImage = new double*[a];
		 for (int i = 0; i<a; i++)		
			 d_proImage[i] = new double [b];		
		imgFT->IFourierEx(d_proImage);
		for(int i=0;i<nHeight;i++)
		{
			for(int j=0;j<nWidth;j++)
			{
			       proImage[i][j] = (int)(d_proImage[i+(a-nHeight)][j]);
			}
		}

		 display_image(proImage);	
			


		 }
private: System::Void idealFilterToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
int *m_height = 0,*m_width = 0;
			 int a = 0;
			 int b = 0;
			 m_height = &a;
			 m_width = &b;
			 double ** d_oriImage = new double*[nHeight];
			 for (int i = 0; i<nHeight;i++)
				 d_oriImage[i] = new double [nWidth];
			 oriImageInitial(0);
			 for(int i=0;i<nHeight;i++)
			 {
				 for(int j=0;j<nWidth;j++)
				 {
					 d_oriImage[i][j] = oriImage[i][j];
				 }
			 }
 Transform_FFT* imgFT = new Transform_FFT(d_oriImage,nWidth,nHeight);
			 imgFT->FourierEx(m_height,m_width);
			 imgFT->IdealLowFilter(proImage,5);
			 display_image(proImage);
		 }			


		 
private: System::Void groupBox2_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void invIdealFilterToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 //zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
			 int *m_height = 0,*m_width = 0;
			 int a = 0;
			 int b = 0;
			 m_height = &a;
			 m_width = &b;
			 double ** d_oriImage = new double*[nHeight];
			 for (int i = 0; i<nHeight;i++)
				 d_oriImage[i] = new double [nWidth];
			 oriImageInitial(0);
			 for(int i=0;i<nHeight;i++)
			 {
				 for(int j=0;j<nWidth;j++)
				 {
					 d_oriImage[i][j] = oriImage[i][j];
				 }
			 }
 Transform_FFT* imgFT = new Transform_FFT(d_oriImage,nWidth,nHeight);
 imgFT->FourierEx(m_height,m_width);
			 imgFT->IdealLowFilter(proImage,5);
			 
 double ** d_proImage = new double*[a];
		 for (int i = 0; i<a; i++)		
			 d_proImage[i] = new double [b];
			 imgFT->IFourierEx(d_proImage);
			 for(int i=0;i<nHeight;i++)
		{
			for(int j=0;j<nWidth;j++)
			{
			       proImage[i][j] = (int)(d_proImage[i+(a-nHeight)][j]);
			}
		}
			 display_image(proImage);
		 }
};
}

