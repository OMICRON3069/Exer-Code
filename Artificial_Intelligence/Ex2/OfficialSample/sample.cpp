//
// Created by Omicron3069 on 6/8/2018.
//

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
typedef int               BOOL;
typedef int               INT;
typedef double         REAL;

//#define FALSE         0
//#define TRUE          1
#define NOT            !
#define AND            &&
#define OR               ||

#define MIN_REAL   -HUGE_VAL
#define MAX_REAL  +HUGE_VAL
#define MIN(x,y)        ((x)<(y) ? (x) : (y))
#define MAX(x,y)       ((x)>(y) ? (x) : (y))

#define LO                 0.1
#define HI                  0.9
#define BIAS              1

#define sqr(x)              ((x)*(x))


typedef struct {                         /* A LAYER OF A NET:                     */
    INT           Units;			/* - number of units in this layer          */
    REAL*         Output;         /* - output of ith unit                          */
    REAL*         Error;           /* - error term of ith unit     每层均方误差                */
    REAL**       Weight;         /* - connection weights to ith unit        */
    REAL**       WeightSave;  /* - saved weights for stopped training */
    REAL**        dWeight;       /* - last weight deltas for momentum  */
    REAL*          Threshold;
    REAL*          ThreSave;
} LAYER;

typedef struct {                              /* A NET:                                */

    LAYER**       Layer;             /* - layers of this net                  */
    LAYER*        InputLayer;       /* - input layer                         */
    LAYER*        OutputLayer;    /* - output layer                        */
    REAL          Alpha;                 /* - momentum factor               */
    REAL          Eta;                    /* - learning rate                       */
    REAL          Gain;                  /* - gain of sigmoid function    sigmoid函数因子  */
    REAL          Error;                 /* - total net error                     整个网络均方误差*/
} NET;


/******************************************************************************
        R A N D O M S   D R A W N   F R O M   D I S T R I B U T I O N S
 ******************************************************************************/


void InitializeRandoms()
{
    srand((unsigned )time(NULL));
}


INT RandomEqualINT(INT Low, INT High)
{
    return rand() % (High-Low+1) + Low;//大于LOW，且小于HIGH
}


REAL RandomEqualREAL(REAL Low, REAL High)
{
    return ((REAL) rand() / RAND_MAX) * (High-Low) + Low;
}


/******************************************************************************
               A P P L I C A T I O N - S P E C I F I C   C O D E
 ******************************************************************************/


#define NUM_LAYERS    3//BP网络层数
#define N                         4//输入特征向量中的元素数
#define M                        3//输出

INT              Units[NUM_LAYERS] = {N, 4, M};//第层所含神经元数


#define NUM_SAMPLE   (150)//样本数

#define TRAIN_LWB        (0)   //下界
#define TRAIN_UPB         (149)//上界
#define TRAIN_SAMPLE  (TRAIN_UPB - TRAIN_LWB + 1)
#define TEST_LWB          (40)
#define TEST_UPB           (60)
#define TEST_SAMPLE     (TEST_UPB - TEST_LWB + 1)
#define EVAL_LWB           (0)
#define EVAL_UPB            (NUM_SAMPLE- 1)
#define EVAL_SAMPLE     (EVAL_UPB - EVAL_LWB + 1)



REAL                 TrainInputSet[NUM_SAMPLE][N];
REAL                 TrainInputSet_[NUM_SAMPLE][N];
REAL                 TrainOutputSet[NUM_SAMPLE][M];


REAL                  Mean;
REAL                  TrainError;
REAL                  TestError;

FILE*                  f;


void NormalizeSample( )//归一化
{

}

void ReadTrainData(string FileName);
void InitializeApplication(NET* Net)
{
    /* INT Sample, i;
     REAL Out, Err;*/
    string  FileName("iris.txt");

    Net->Alpha = 0.5;//初始化动量常数
    Net->Eta     = 0.05;//学习率
    Net->Gain   = 1;   //S型的函数值


    ReadTrainData( FileName);
    f = fopen("BPN.txt", "w");
}


void FinalizeApplication(NET* Net)
{
    fclose(f);
}


/******************************************************************************
                          I N I T I A L I Z A T I O N
 ******************************************************************************/


void GenerateNetwork(NET* Net)
{
    INT l,i;

    Net->Layer = (LAYER**) calloc(NUM_LAYERS, sizeof(LAYER*));

    for (l=0; l<NUM_LAYERS; l++)
    {
        Net->Layer[l] = (LAYER*) malloc(sizeof(LAYER));

        Net->Layer[l]->Units          = Units[l];
        Net->Layer[l]->Output        = (REAL*)  calloc(Units[l]+1, sizeof(REAL));
        Net->Layer[l]->Error          = (REAL*)  calloc(Units[l]+1, sizeof(REAL));
        Net->Layer[l]->Weight        = (REAL**) calloc(Units[l]+1, sizeof(REAL*));
        Net->Layer[l]->WeightSave = (REAL**) calloc(Units[l]+1, sizeof(REAL*));
        Net->Layer[l]->dWeight      = (REAL**) calloc(Units[l]+1, sizeof(REAL*));
        Net->Layer[l]->Threshold    = (REAL *) calloc(Units[l]+1,sizeof(REAL));
        Net->Layer[l]->ThreSave    = (REAL *) calloc(Units[l]+1,sizeof(REAL));
        Net->Layer[l]->Output[0]    = BIAS;
        if (l != 0)
        {
            for (i=1; i<=Units[l]; i++)
            {
                Net->Layer[l]->Weight[i]        = (REAL*) calloc(Units[l-1]+1, sizeof(REAL));
                Net->Layer[l]->WeightSave[i] = (REAL*) calloc(Units[l-1]+1, sizeof(REAL));
                Net->Layer[l]->dWeight[i]      = (REAL*) calloc(Units[l-1]+1, sizeof(REAL));
            }
        }
    }
    Net->InputLayer   = Net->Layer[0];
    Net->OutputLayer = Net->Layer[NUM_LAYERS - 1];
    Net->Alpha           = 0.9;
    Net->Eta               = 0.25;
    Net->Gain             = 1;
}


void RandomWeights(NET* Net)
{
    INT l,i,j;

    for (l=1; l<NUM_LAYERS; l++)
    {
        for (i=1; i<=Net->Layer[l]->Units; i++)
        {
            for (j=0; j<=Net->Layer[l-1]->Units; j++)
            {
                Net->Layer[l]->Weight[i][j] = RandomEqualREAL(-0.5, 0.5);
            }
            Net->Layer[l]->Threshold[i] = RandomEqualREAL(-0.5,0.5);
        }
    }
}


void SetInput(NET* Net, REAL* Input)
{
    INT i;

    for (i=1; i<=Net->InputLayer->Units; i++)
    {
        Net->InputLayer->Output[i] = Input[i-1];
    }
}


void GetOutput(NET* Net, REAL* Output)
{
    INT i;

    for (i=1; i<=Net->OutputLayer->Units; i++)
    {
        Output[i-1] = Net->OutputLayer->Output[i];
    }
}


void ReadTrainData(string FileName)
{
    ifstream InFile;
    string LineData;
    REAL SingleData;

    InFile.open(FileName.c_str(),ios_base::in);
    if (! InFile)
    {
        cerr<<"error: unable to open:"<< FileName<<endl;
    }

    for ( int i = 0; i < NUM_SAMPLE; i++)
    {
        if ( getline ( InFile, LineData) )
        {
            cout<<"特征向量:";
            istringstream stream ( LineData );
            for ( int j = 0;j < N;j ++ )
            {
                stream >> SingleData;
                TrainInputSet [ i ][ j ]  =  SingleData;
                TrainInputSet_[ i ][ j ] =  SingleData;
                cout<<TrainInputSet[i][j]<<"\t";
            }//end N


            if(i<50)
            {
                TrainOutputSet[ i ][0]=1;
                TrainOutputSet[ i ][1]=0;
                TrainOutputSet[ i ][2]=0;
            }
            else if(i<100)
            {
                TrainOutputSet[ i ][0]=0;
                TrainOutputSet[ i ][1]=1;
                TrainOutputSet[ i ][2]=0;
            }
            else if(i<150)
            {
                TrainOutputSet[ i ][0]=0;
                TrainOutputSet[ i ][1]=0;
                TrainOutputSet[ i ][2]=1;
            }
            cout<<"期望输出:";
            for(int k=0;k<M;k++)
            {
                cout<<TrainOutputSet[ i ][k]<<" ";
            }

            cout<<endl;
        }//end if getline
    }//end for NUM_SAMPLE

    InFile.close( );

}
/******************************************************************************
            S U P P O R T   F O R   S T O P P E D   T R A I N I N G
 ******************************************************************************/


void SaveWeights(NET* Net)
{
    INT l,i,j;

    for (l=1; l<NUM_LAYERS; l++)
    {
        for (i=1; i<=Net->Layer[l]->Units; i++)
        {
            for (j=0; j<=Net->Layer[l-1]->Units; j++)
            {
                Net->Layer[l]->WeightSave[i][j] = Net->Layer[l]->Weight[i][j];
            }
            Net->Layer[l]->ThreSave[i] = Net->Layer[l]->Threshold[i];
        }
    }
}


void RestoreWeights(NET* Net)
{
    INT l,i,j;

    for (l=1; l<NUM_LAYERS; l++)
    {
        for (i=1; i<=Net->Layer[l]->Units; i++)
        {
            for (j=0; j<=Net->Layer[l-1]->Units; j++)
            {
                Net->Layer[l]->Weight[i][j] = Net->Layer[l]->WeightSave[i][j];
            }
            Net->Layer[l]->Threshold[i] = Net->Layer[l]->ThreSave[i];
        }
    }
}


/******************************************************************************
                     P R O P A G A T I N G   S I G N A L S
 ******************************************************************************/

//求高层神经元输入和输出
void PropagateLayer(NET* Net, LAYER* Lower, LAYER* Upper)
{
    INT  i,j;
    REAL Sum;

    for (i=1; i<=Upper->Units; i++)
    {
        Sum = 0;
        for (j=0; j<=Lower->Units; j++)
        {
            Sum += Upper->Weight[i][j] * Lower->Output[j];
        }
        Sum -= Upper->Threshold[i];//计算Upper层第i单元的激活值
        Upper->Output[i] = 1. / (1. + exp(-Net->Gain * Sum));//Upper层i单元的输出值
    }
}


void PropagateNet(NET* Net)
{
    INT l;

    for (l=0; l<NUM_LAYERS-1; l++)//计算从第一隐藏层到输出层的输出值
    {
        PropagateLayer(Net, Net->Layer[l], Net->Layer[l+1]);
    }
}


/******************************************************************************
                  B A C K P R O P A G A T I N G   E R R O R S
 ******************************************************************************/
//求上面输出层输出值与样本值（期望值）之间的差距
void ComputeOutputError(NET* Net, REAL* Target)
{//Target为期望输出
    INT  i;
    REAL Out, Err;

    Net->Error = 0;
    for (i=1; i<=Net->OutputLayer->Units; i++)
    {
        Out = Net->OutputLayer->Output[i];//输出层实际输出
        Err = Target[i-1]-Out;//期望输出－实际输出
        Net->OutputLayer->Error[i] = Net->Gain * Out * (1-Out) * Err;//输出层的校正误差
        Net->Error += 0.5 * sqr(Err);//计算均方误差
    }
}


void BackpropagateLayer(NET* Net, LAYER* Upper, LAYER* Lower)
{//Lower层各单元的校正误差
    INT  i,j;
    REAL Out, Err;

    for (i=1; i<=Lower->Units; i++)
    {
        Out = Lower->Output[i];
        Err = 0;
        for (j=1; j<=Upper->Units; j++)
        {
            Err += Upper->Weight[j][i] * Upper->Error[j];
        }
        Lower->Error[i] = Net->Gain * Out * (1-Out) * Err;
    }
}


void BackpropagateNet(NET* Net)
{
    INT l;

    for (l=NUM_LAYERS-1; l>1; l--) //计算中间层各单元的校正误差
    {
        BackpropagateLayer(Net, Net->Layer[l], Net->Layer[l-1]);
    }
}


void AdjustWeights(NET* Net)
{
    INT  l,i,j;
    REAL Out, Err, dWeight;

    for (l=1; l<NUM_LAYERS; l++)
    {
        for (i=1; i<=Net->Layer[l]->Units; i++)
        {
            for (j=0; j<=Net->Layer[l-1]->Units; j++)
            {
                Out = Net->Layer[l-1]->Output[j];
                Err = Net->Layer[l]->Error[i];
                dWeight = Net->Layer[l]->dWeight[i][j];
                Net->Layer[l]->Weight[i][j] += Net->Eta * Err * Out + Net->Alpha * dWeight;
                Net->Layer[l]->dWeight[i][j] = Net->Eta * Err * Out;
            }
            Net->Layer[l]->Threshold[i] =  Net->Eta * Err;
        }
    }
}


/******************************************************************************
                      S I M U L A T I N G   T H E   N E T
 ******************************************************************************/


void SimulateNet(NET* Net, REAL* Input, REAL* Output, REAL* Target, BOOL Training)
{ //Input是输入向量，Output是实际输出，Target是期望输出，Training是判断是否训练
    SetInput(Net, Input);
    PropagateNet(Net);
    GetOutput(Net, Output);

    ComputeOutputError(Net, Target);
    if (Training)
    {
        BackpropagateNet(Net);
        AdjustWeights(Net);
    }
}


void TrainNet(NET* Net, INT Epochs)
{
    INT  Sample, n;
    REAL Output[M];

    for (n=0; n<Epochs*TRAIN_SAMPLE; n++)
    {
        Sample = RandomEqualINT(TRAIN_LWB, TRAIN_UPB);
        SimulateNet(Net, TrainInputSet[Sample], Output, TrainOutputSet[Sample],true);
    }
}


void TestNet(NET* Net)
{
    INT  Sample;
    REAL Output[M];

    TrainError = 0;
    for (Sample=TRAIN_LWB; Sample<=TRAIN_UPB; Sample++)
    {
        SimulateNet(Net, TrainInputSet[Sample], Output, TrainOutputSet[Sample], false);
        TrainError += Net->Error;
    }
    TestError = 0;
    for (Sample=TEST_LWB; Sample<=TEST_UPB; Sample++)
    {
        SimulateNet(Net,TrainInputSet[Sample], Output, TrainOutputSet[Sample], false);
        TestError += Net->Error;
    }
    fprintf(f, "\nNMSE is    %.4f     on Training Set and    %.4f    on Test Set",
            TrainError ,
            TestError);
}


void EvaluateNet(NET* Net)
{
    INT  Sample;
    REAL Output [M];
    //REAL Output_[M];

    fprintf(f, "\n\n\n");
    fprintf(f, "Num                 TrainInputSet{1,2,3,4}　    TrainOutputSet{123}　            Prediction ");
    fprintf(f, "\n");
    for (Sample=EVAL_LWB; Sample<=EVAL_UPB; Sample++)
    {
        SimulateNet(Net, TrainInputSet[Sample], Output, TrainOutputSet[Sample], false);

        fprintf(f, "%d      %0.2f     %0.2f      %0.2f     %0.2f      %0.1f  %0.1f  %0.1f             %0.3f      %0.3f     %0.3f\n   ",
                Sample,
                TrainInputSet[Sample][0],
                TrainInputSet[Sample][1],
                TrainInputSet[Sample][2],
                TrainInputSet[Sample][3],
                TrainOutputSet[Sample][0],
                TrainOutputSet[Sample][1],
                TrainOutputSet[Sample][2],
                Output[0],
                Output[1],
                Output[2]
        );

    }

}


/******************************************************************************
                                    M A I N
 ******************************************************************************/


int main()
{
    NET  Net;
    BOOL Stop;


    InitializeRandoms();
    GenerateNetwork(&Net);
    RandomWeights(&Net);
    InitializeApplication(&Net);

    Stop = false;
    do {
        TrainNet(&Net, 1);
        TestNet(&Net);
        if (TestError>0.0001)
        {
            SaveWeights(&Net);
        }
        else
        {
            Stop = true;
            RestoreWeights(&Net);
        }
    } while (NOT Stop);

    TestNet(&Net);
    EvaluateNet(&Net);

    FinalizeApplication(&Net);
}