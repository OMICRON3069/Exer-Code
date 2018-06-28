# include "hszy.h"
using namespace std;//C++命名空间

int main( ) {
	srand((unsigned)time( NULL ) );
	Population a;
	a.traverse();
	int count = 0,  gen = 0;//count表示，gen 表示代数
	for(int i=0;i<150;i++) {
		Individuality temp = a.getMax();
		a.inherit();
		if(a.getMax() == temp)
			{count++;}
		if(count>30) 
			break;
		a.traverse();
		gen++;
	}
	a.getMax().print();
	cout << "After " << gen << " generations.\n";
	cout<<RAND_MAX<<endl;
	cout<<sum/co << "\n";
	//system("pause");  //这里让系统暂停
	return 0;
}
