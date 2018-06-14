#include <iostream>
#include <fstream>
#include <stack> 
#include <string.h>
#define MAX 8
#define RIGHT 1
#define ERROR -1
#define GOAHEAD 0 

using namespace std;

string border[MAX] = { ",", ".", ";", "(", ")", "{", "}" };
string operators[MAX] = { "+", "-", "*", "/", "=", "<", ">", "%" };

char Vt[MAX] = { 'i', '+', '-', '*', '/', '(', ')', '#' };//存放终结符
char* VnE[MAX] = { "TA", "", "", "", "", "TA", "", "" };//对应行 E
char* VnA[MAX] = { "", "+TA", "-TA", "", "", "", "0", "0" };//对应行 E'， 0 对应ε
char* VnT[MAX] = { "FB", "", "", "", "", "FB", "", "" };//对应行 T
char* VnB[MAX] = { "", "0", "0", "*FB", "/FB", "", "0", "0" };//对应行 T'
char* VnF[MAX] = { "i", "", "", "", "", "(E)", "", "" };//对应行 F

char transString[1000];//存放通过词法分析得到的输入串 
char buffer[1000];//缓冲区：存放文件读取的数据 
char ch = ' ';
int chCount = 0;//getCh();计数器 
int tCount = 0;//getTransString();计数器 
int result = 0;//存放分析结果 
int numOfSharp = 0;  //句子数
int nowNumOfSharp = 0; //当前分析的句子数
stack<char> aStack;  //分析栈 

//判断是否是数字 
bool isNumber(char c) {
	if (c >= '0' && c <= '9') {
		return true;
	} else {
		return false;
	}
}

//判断是否是运算符  测试正确 
bool isOperator(char c) {
	string str;
	str += c;
	int k, i;
	int len = sizeof(operators) / sizeof(string);
	for (i = 0; i < len; i++) {
		k = operators[i].compare(str);
		if (k == 0) {
			return true;
		}
	}
	if (i == len) {
		return false;
	}
}

//判断是否是界符 测试正确 
bool isBorder(char c) {
	string str;
	str += c;
	int len = sizeof(border) / sizeof(string);
	int k, i;
	for (i = 0; i < len; i++) {
		k = border[i].compare(str);
		if (k == 0) {
			return true;
		}
	}
	if (i == len) {
		return false;
	}
}

//判断是否是终结符 
bool isVt(char x) {
	int k;
	for (k = 0; k < MAX; k++) {
		if (Vt[k] == x) {
			return true;
		}
	}
	if (k == MAX) {
		return false;
	}
}

//从buf中取字符 
char getCh(char* buf) {
	char tmp = buf[chCount];
	chCount = chCount + 1;
	return tmp;
}

//将表达式转换成输入串形式    
void getTransString() { 
	while ((ch == ' ' || ch == '\n')) {
		ch = getCh(buffer);
	} 
	if (isNumber(ch)) {
		while (isNumber(ch)) {
			ch = getCh(buffer);
		}
		transString[tCount] = 'i';
		tCount++;
	} else {
		if (isOperator(ch)) {
			transString[tCount] = ch;
			tCount++;
			ch = getCh(buffer);
		} else {
			if (isBorder(ch)) {
				if (ch == ';') {
					transString[tCount] = '#';
					numOfSharp += 1;
				} else {
					transString[tCount] = ch;
				}
				tCount++;
				ch = getCh(buffer);
			}
		}
	}
}

//查表得到产生式 
char* getProduction(char x, char a) {
	char* pro;
	int k;
	for (k = 0; k < MAX; k++) {
		if (Vt[k] == a) {
			switch (x) {
			case 'E':
				pro = VnE[k];
				break;
			case 'A':
				pro = VnA[k];
				break;
			case 'T':
				pro = VnT[k];
				break;
			case 'B':
				pro = VnB[k];
				break;
			case 'F':
				pro = VnF[k];
				break;
			}
			break;
		}
	}
	return pro;
}

//语法分析 
int syntaxAnalysis() {
	char a; //a存放当前终结符
	char X;//存放弹出的栈顶符号,  
	char* pro;//存放产生式 
	int len = 0;
	a = getCh(transString);
	X = aStack.top();
	while (X != a) {
		if (!isVt(X)) {
			pro = getProduction(X, a);
			aStack.pop();
			len = strlen(pro);
			if (len != 0) {
				if (pro != "0") {
					for (int j = len - 1; j >= 0; j--) {
						aStack.push(pro[j]);
					}
				}
			} else {
				cout << "出错, 错误位置为：" << X << "与" << a << "查表失败" << endl << endl;
				nowNumOfSharp += 1;
				while(a != '#') {    //将a的位置移到下一句句首 
					a = getCh(transString);
				}
				return ERROR;
			}
		} else {
			cout << "出错，错误位置为：" << X << "与" << a << "不匹配" << endl << endl;
			nowNumOfSharp += 1;
			while(a != '#') {
				a = getCh(transString);
			}
			return ERROR;
		}
		X = aStack.top();
		if (X == '#' && a == '#') {
			cout << "句子正确" << endl << endl;
			nowNumOfSharp += 1;
			return RIGHT;
		}
	}

	aStack.pop();
	return GOAHEAD;
}
 
void getStringFromFile(char* fileName) {
	char c;
	int i = 0;
	freopen(fileName, "r", stdin);
	while (~scanf("%c", &c)) {
		buffer[i] = c;
		i++;
		if (c == ' ' || c == '\n') {
			i--;
		}	
	}
	while (ch != '\n') {   //i记录的是buffer字符数，tCount记录的是transString中的字符数 
		getTransString();
	}
}

int main() {
	aStack.push('#');
	aStack.push('E');
	getStringFromFile("test2.txt");
	
freopen("out.txt", "w", stdout);
	chCount = 0;
		A:
		while(result == 0) {
			result = syntaxAnalysis();
		}
		if (numOfSharp != nowNumOfSharp) {
			result = 0;
			while (!aStack.empty()) {
				aStack.pop();
			}
			aStack.push('#');
			aStack.push('E');
			goto A;
		}
	return 0;
}
