#pragma once

namespace fword {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}
		public:
	    typedef  unsigned char BYTE;
	    Bitmap^  original_bmap;
	    Bitmap^  processed_bmap;

	     int nWidth;                 //图像宽
	     int nHeight;                //图像高

	     BYTE **oriImage;           //原图灰度
		 BYTE **proImage;          //处理后灰度
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
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
	private: System::Windows::Forms::ToolStripMenuItem^  edgeDetectToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  sobelToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::ToolStripMenuItem^  laplaceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  prewittToolStripMenuItem;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
void Sobel(double **tenA,double **tenB,int tenNo,int nWidth, int nHeight,BYTE **formerImage,BYTE **imageT)
  {
	double **imageT1;
	double **imageT2;
	double sum = 0;
	imageT1 = new double *[nHeight];
	imageT2 = new double *[nHeight];
	for(int i=0;i<nHeight;i++)
	{
		imageT1[i]=new double[nWidth];
		imageT2[i]=new double[nWidth];
	}
	Template(tenA,tenNo,nWidth,nHeight,formerImage,imageT1);
	Template(tenB,tenNo,nWidth,nHeight,formerImage,imageT2);
	for( int i=0; i<nHeight; i++ )
	{
		for( int j=0; j<nWidth; j++)
		{
		           sum= Math::Pow(imageT1[i][j]*imageT1[i][j] +imageT2[i][j]*imageT2[i][j],1);	         
				   if(sum>255)      sum=255;		
		           if(sum<0)        sum=0;	
		           imageT[i][j] = (BYTE)sum;
		}
	}
for( int i=0; i<nHeight; i++ )
	{
	   	delete []imageT1[i];
	  	 delete []imageT2[i];
	}
   delete []imageT1;
   delete []imageT2;
}

void Laplace(double **tenA,int tenNo,int nWidth, int nHeight,BYTE **formerImage,BYTE **imageT)
  {
	double **imageT1;
	//double **imageT2;
	double sum = 0;
	imageT1 = new double *[nHeight];
	//imageT2 = new double *[nHeight];
	
	for(int i=0;i<nHeight;i++)
	{
		imageT1[i]=new double[nWidth];
		//imageT2[i]=new double[nWidth];
	}
	
	Template(tenA,tenNo,nWidth,nHeight,formerImage,imageT1);
	//Template(tenB,tenNo,nWidth,nHeight,formerImage,imageT2);
	
	for( int i=0; i<nHeight; i++ )
	{
		for( int j=0; j<nWidth; j++)
		{
		           sum= Math::Pow(imageT1[i][j]*imageT1[i][j] /*+imageT2[i][j]*imageT2[i][j]*/,1);
					//sum = imageT1[i][j];
				   if(sum>255)      sum=255;		
		           if(sum<0)        sum=0;	
		           imageT[i][j] = (BYTE)sum;
		}
	}
	
for( int i=0; i<nHeight; i++ )
	{
	   	delete []imageT1[i];
	  	// delete []imageT2[i];
	}
   delete []imageT1;
  // delete []imageT2;
}

void prewitt(double **tenA,double **tenB,int tenNo,int nWidth, int nHeight,BYTE **formerImage,BYTE **imageT)
  {
	double **imageT1;
	double **imageT2;
	double sum = 0;
	imageT1 = new double *[nHeight];
	imageT2 = new double *[nHeight];
	for(int i=0;i<nHeight;i++)
	{
		imageT1[i]=new double[nWidth];
		imageT2[i]=new double[nWidth];
	}
	Template(tenA,tenNo,nWidth,nHeight,formerImage,imageT1);
	Template(tenB,tenNo,nWidth,nHeight,formerImage,imageT2);
	for( int i=0; i<nHeight; i++ )
	{
		for( int j=0; j<nWidth; j++)
		{
		           sum= Math::Pow(imageT1[i][j]*imageT1[i][j] +imageT2[i][j]*imageT2[i][j],1);	         
				   if(sum>255)      sum=255;		
		           if(sum<0)        sum=0;	
		           imageT[i][j] = (BYTE)sum;
		}
	}
for( int i=0; i<nHeight; i++ )
	{
	   	delete []imageT1[i];
	  	 delete []imageT2[i];
	}
   delete []imageT1;
   delete []imageT2;
}

void display_image(Bitmap^ bmap,BYTE **grey)//此处原int变为BYTE                                                        
{
	 for(int i=0;i<nHeight;i++)
      {
		for(int j=0;j<nWidth;j++)
		 {						  
		       bmap-> SetPixel  (j,i,Color::FromArgb(grey[i][j],grey[i][j],grey[i][j]));  
		}
	}
}
void Template(double **ten,int tenNo,int nWidth, int nHeight,BYTE **formerImage,double **imageT)
{
	//模板四个方向上的宽度变量
	int No=tenNo/2;

	//模板四个方向和原图形的重叠量
	int front=0;
	int back=0;
	int left=0;
	int right=0;

	double sum=0;
for(int i=0;i<nHeight;i++)
	{
		for(int j=0;j<nWidth;j++)
		{
			//求模板四个方向和原图形的重叠量
			if(i<No)                         front=i;	
			else                                front=No;	
			if(nHeight-i-1<No)      back=nHeight-i-1;	
			else                                back=No;	
			if(j<No)                         right=j;	
			else                                right=No;
			if(nWidth-j-1<No)       left=nWidth-j-1;
			else                                left=No;
			sum=0;
//求取当前点区域和模板卷积的结果
			for(int h=-front;h<=back;h++)
			{
				for(int k=-right;k<=left;k++)
				{			   
                    sum+=ten[h+No][k+No]*((double)formerImage[i+h][j+k]);
				}
			}
	        
			//存储处理结果
			imageT[i][j]=sum;
		   }	
	}
} 	

		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->edgeDetectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sobelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->laplaceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->prewittToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
				this->edgeDetectToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(833, 25);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->openToolStripMenuItem, 
				this->saveToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(39, 21);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(108, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(108, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveToolStripMenuItem_Click);
			// 
			// edgeDetectToolStripMenuItem
			// 
			this->edgeDetectToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->sobelToolStripMenuItem, 
				this->laplaceToolStripMenuItem, this->prewittToolStripMenuItem});
			this->edgeDetectToolStripMenuItem->Name = L"edgeDetectToolStripMenuItem";
			this->edgeDetectToolStripMenuItem->Size = System::Drawing::Size(87, 21);
			this->edgeDetectToolStripMenuItem->Text = L"EdgeDetect";
			// 
			// sobelToolStripMenuItem
			// 
			this->sobelToolStripMenuItem->Name = L"sobelToolStripMenuItem";
			this->sobelToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->sobelToolStripMenuItem->Text = L"sobel";
			this->sobelToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::sobelToolStripMenuItem_Click);
			// 
			// laplaceToolStripMenuItem
			// 
			this->laplaceToolStripMenuItem->Name = L"laplaceToolStripMenuItem";
			this->laplaceToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->laplaceToolStripMenuItem->Text = L"laplace";
			this->laplaceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::laplaceToolStripMenuItem_Click);
			// 
			// prewittToolStripMenuItem
			// 
			this->prewittToolStripMenuItem->Name = L"prewittToolStripMenuItem";
			this->prewittToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->prewittToolStripMenuItem->Text = L"prewitt";
			this->prewittToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::prewittToolStripMenuItem_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Location = System::Drawing::Point(12, 28);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(362, 298);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(19, 20);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(300, 256);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->pictureBox2);
			this->groupBox2->Location = System::Drawing::Point(477, 38);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(315, 288);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"2";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(21, 21);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(275, 245);
			this->pictureBox2->TabIndex = 0;
			this->pictureBox2->TabStop = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(833, 366);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->groupBox2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				  OpenFileDialog^ openFile1 = gcnew OpenFileDialog ( );
	 openFile1->InitialDirectory = "E:\\";
	 openFile1 ->Filter = "Bitmap Image(*.bmp)|*.bmp|Image(*.jpeg)|*.jpg";
	 openFile1 ->RestoreDirectory = true;

	 if (openFile1 ->ShowDialog() == Windows::Forms::DialogResult ::OK) 
	     {
		String^ fileName = openFile1 ->FileName->ToString();

		original_bmap  = gcnew Bitmap ( fileName, true );
		processed_bmap = gcnew Bitmap ( fileName, true );

		 nWidth  = original_bmap->Width;
		 nHeight = original_bmap->Height;
		  pictureBox1->Image = original_bmap;
	  pictureBox2->Image = processed_bmap;
	 pictureBox1->Refresh();
	 pictureBox2->Refresh();

      oriImage = new BYTE*[nHeight];
	 proImage = new BYTE *[nHeight];

	 for ( int i = 0; i < nHeight; i++ )
       {
                oriImage[i] = new BYTE[nWidth];
	          proImage[i] = new BYTE[nWidth];
	  }
	 for ( int i = 0; i < nHeight; i++ )
     {
               for ( int j = 0; j < nWidth; j++ )
	          {
		 oriImage[i][j] = (BYTE)(original_bmap->GetPixel(j,i).R*0.299
 + original_bmap->GetPixel(j,i).G*0.587  
  + original_bmap->GetPixel(j,i).B*0.114);
		 }
         }				 
     } // end if

			 }
private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 	 SaveFileDialog ^ saveFile1 = gcnew SaveFileDialog ();
saveFile1 -> InitialDirectory = "E:\\";
saveFile1 -> Filter = "Bitmap Image|*.bmp|JPeg Image|*.jpg|Gif Image|*.gif";
saveFile1 -> Title = "Save an Image File";
saveFile1 -> ShowDialog ();
if ( saveFile1 ->FileName != " ")
{
	switch( saveFile1->FilterIndex )
	 {
		 case 1:
		 this->processed_bmap->Save(saveFile1->   FileName , System:: Drawing :: Imaging::   ImageFormat::Jpeg);
		            break;
case 2:
	    this->processed_bmap->Save(saveFile1->FileName ,System ::Drawing :: Imaging :: ImageFormat ::Bmp);
		              break;

		case 3:
	    this->processed_bmap->Save(saveFile1->FileName,System ::Drawing :: Imaging :: ImageFormat ::Gif);
		              break;
		 } //end switch
	 } // end if

		 }
private: System::Void sobelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 double ten11[3][3] = {{-1.0/8.0,-2.0/8.0,-1.0/8.0},{0,0,0},{1.0/8.0,2.0/8.0,1.0/8.0}};
			double ten22[3][3] = {{-1.0/8.0,0,1.0/8.0},{-2.0/8.0,0,2.0/8.0},{-1.0/8.0,0,1.0/8.0}}; 
			double **ten1;
			double **ten2;
			int tenNo = 3;
			ten1 = new double *[tenNo];
			ten2 = new double *[tenNo];
			for( int i=0; i<tenNo; i++ )
			{
				ten1[i] = new double [tenNo];
				ten2[i] = new double [tenNo];
			}
			for( int i=0; i<tenNo; i++ )
			{
				for( int j=0; j<tenNo; j++ )
				 {		
					ten1[i][j] = ten11[i][j];
					ten2[i][j] = ten22[i][j];
				}
			}

			Sobel(ten1, ten2, tenNo, nWidth, nHeight, oriImage, proImage);
			for( int i=0; i<tenNo; i++)
			{
				delete []ten1[i];
				delete []ten2[i];
			}
			delete []ten1;
			delete []ten2;
			display_image( processed_bmap, proImage );
			pictureBox2->Refresh();
	 }
private: System::Void laplaceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			double shit211[3][3] = {{0,-1.0/8.0,1.0/8.0},{-1.0/8.0,4.0/8.0,-1.0/8.0},{0,-1.0/8.0,0}};
			double shit985[3][3] = {{-1.0/8.0,-1.0/8.0,-1.0/8.0},{-1.0/8.0,8.0/8.0,-1.0/8.0},{-1.0/8.0,-1.0/8.0,-1.0/8.0}}; 
			double **shit2111;
			double **shit9855;
			int tenNo = 3;
			shit2111 = new double *[tenNo];
			shit9855 = new double *[tenNo];
			for( int i=0; i<tenNo; i++ )
			{
				shit2111[i] = new double [tenNo];
				shit9855[i] = new double [tenNo];
			}
			for( int i=0; i<tenNo; i++ )
			{
				for( int j=0; j<tenNo; j++ )
				 {		
					shit2111[i][j] = shit211[i][j];
					shit9855[i][j] = shit985[i][j];
				}
			}

			Laplace(shit9855, tenNo, nWidth, nHeight, oriImage, proImage);
			for( int i=0; i<tenNo; i++)
			{
				delete []shit2111[i];
				delete []shit9855[i];
			}
			delete []shit2111;
			delete []shit9855;
			display_image( processed_bmap, proImage );
			pictureBox2->Refresh();
		 } 
private: System::Void prewittToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			double ten11[3][3] = {{-1.0/6.0,0/6.0,1.0/8.0},{-1.0/8.0,0/8.0,1.0/8.0},{-1.0/8.0,0/8.0,1.0/8.0}};
			double ten22[3][3] = {{-1.0/8.0,-1.0/8.0,-1.0/8.0},{0,0,0},{1.0/8.0,1.0/8.0,1.0/8.0}}; 
			double **ten1;
			double **ten2;
			int tenNo = 3;
			ten1 = new double *[tenNo];
			ten2 = new double *[tenNo];
			for( int i=0; i<tenNo; i++ )
			{
				ten1[i] = new double [tenNo];
				ten2[i] = new double [tenNo];
			}
			for( int i=0; i<tenNo; i++ )
			{
				for( int j=0; j<tenNo; j++ )
				 {		
					ten1[i][j] = ten11[i][j];
					ten2[i][j] = ten22[i][j];
				}
			}

			prewitt(ten1, ten2, tenNo, nWidth, nHeight, oriImage, proImage);
			for( int i=0; i<tenNo; i++)
			{
				delete []ten1[i];
				delete []ten2[i];
			}
			delete []ten1;
			delete []ten2;
			display_image( processed_bmap, proImage );
			pictureBox2->Refresh();
		 }
};
}

