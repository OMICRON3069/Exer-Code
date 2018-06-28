#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include<cstdio>

const int MAX = 4194304;
const int MIN = 0;
const int POP_SIZE = 100;
int co=0;
double sum=0;

using namespace std;// c++标准命名空间，作用域范围
const float pi = 3.1415926f;
class Individuality {
private:
	int chromosome;	//染色体
public:
	void set (int chromosome){ 
		this->chromosome = chromosome;}

	Individuality operator = (Individuality c) { 
		this->chromosome = c.chromosome;
		return *this; 
	}

	bool operator ==(Individuality c) { 
		return this->chromosome == c.chromosome; }
	
	float resolve() {    //通过染色体取得x的值.返回值在(-1,2)之间
		return  0 + (float)chromosome  / (MAX -1);
	}

	float evaluate() {	//f()，评价函数
		return (float)10*sin(5*resolve()) + (float)7*cos(4*resolve());
	}

	void print() {  //打印函数
		cout << '\t';
		for(int j = 21; j >= 0; j--)
		if((1<<j) & chromosome) cout << '1';
		else cout << '0';
		printf("\t\tx=%f\tf(x) = %f\n", resolve(), evaluate() );
		co++;
		sum+=evaluate();
	}

	Individuality variate() {     //变异函数
		int  i = rand() % 21 + 1; //i在1-22之间
		this->chromosome ^= 1<<i;   //i左移i位，再与chromosome异或
		return *this;
	}

	void crisscross (Individuality prnt1,  Individuality prnt2, Individuality &child1, Individuality &child2) {   // 两个体交叉操作
		int i = rand( ) % 21 + 1;  //i在-22之间，表示随机在两位之间交叉
		int temp1 = prnt1.chromosome;
		int temp2 = prnt2.chromosome;
		int temp = 0;
		for(; i < 22; i++) { //i在上面已赋初值，故for循环表达式1可省略
			i<<1;
			temp += i;
		}
		temp1 &= temp;
		temp2 &= temp;
		prnt1.chromosome &= (~temp);
		prnt2.chromosome &= (~temp);
		prnt1.chromosome |= temp2;
		prnt2.chromosome |= temp1;
		child1 = prnt1;
		child2 = prnt2;

	}
};

class Population {
private:	
	Individuality ind[POP_SIZE]; //所有的个体
public:
    Population() {
        for(int i = 0; i < POP_SIZE; i++)		
			ind[i].set( (((double)rand()/(double)RAND_MAX)* MAX + MIN) ); //产的随机数是0~2的22次方（4194304）之间
	}
	
	void  shellSort() {  //希尔排序
	   int gap, i, j;
	   Individuality temp;
	   for(gap = POP_SIZE/2; gap > 0;gap /= 2)
		   for(i = gap; i < POP_SIZE; i++)
			   for(j=i-gap; j>=0 && ind[j].evaluate() < ind[j+gap].evaluate(); j -= gap){
				   temp= ind[j];
				   ind[j] = ind[j+gap];
				   ind[j+gap] = temp;
			   }
	}

    void inherit() {  //遗传操作
		int i, n1, n2;
		Population::shellSort();  //对种群进行希尔排序
		const int NT = POP_SIZE / 2;
		Individuality temp[NT];
		for(int i = 0; i < NT; i++)
		temp[i] = ind[i];     //种群排队，选大的那一半放temp数组
		int nc = (rand( ) % (POP_SIZE/10) + (POP_SIZE/4)) / 2;
		int nv = rand() % (POP_SIZE/100+1) + (POP_SIZE/100);
		for(i = 0; i<nv; i++) {//变异
			n1 = rand( ) % NT;
			ind[i] = temp[n1].variate();  
		}
		for(i = nv; i < nc; i += 2) {  //交叉
		n1 = rand() % NT;
		n2 = rand() % NT;
		Individuality temp1, temp2;
		temp->crisscross(temp[n1], temp[n2], temp1, temp2);
		ind[i] = temp1; ind[i+1] = temp2;  
        }

		for(i = nv+nc*2; i < POP_SIZE; i++) {   //直接复制
			n1 = rand() % NT;
			ind[i] = temp[n1];
		}
	} // inherit

	Individuality getMax() { //获取种群适应度函数最高的个体
		Individuality max = ind[0];
		for(int i = 0; i < POP_SIZE-1; i++) {
			if( ind[i+1].evaluate() > ind[i].evaluate() ) 
				max = ind[i+1];  }
		return max;
	}

	void traverse() {
		for(int i = 0; i < POP_SIZE; i++)
		ind[i].print();
		cout << endl;
	}
};
