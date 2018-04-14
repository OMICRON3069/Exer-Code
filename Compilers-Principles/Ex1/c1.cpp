#include <iostream>
#include <cstdio> 
#include <fstream>
#include <stdlib.h>
#include <string>
#define MAX 20

using namespace std;

string borderKey[MAX] = {"comma", "point", "semicolon", "lparen", "rparen", "lbparen", "rbparen"};
string border[MAX] = {",", ".", ";", "(", ")", "{", "}"};
string reservedWord[MAX] = {"main", "if", "else", "int", "return", "do", "continue", "break"};
string operatorsKey[MAX] = {"plus", "sub", "multi", "devide", "pound", "greatOrEqual", "lessOrEqual", "less", "greater", "percent"};
string operators[MAX] = {"+", "-", "*", "/", "=", ">=", "<=", "<", ">", "%"};
string sym;
string value;
char buffer[1000]; 
char ch = ' ';
int count = 0;//计数器 

//判断是否是字母 (测试正确)
bool isLetter(char c) {
	if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
		return true;
	} else {
		return false;
	}
}

//判断是否是数字 
bool isNumber(char c) {
	if(c >= '0' && c <= '9') {
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
	int len = sizeof(operators)/sizeof(string);
	for(i = 0; i < len; i++ ) {
		k = operators[i].compare(str);
		if(k == 0) {
			return true;
		} 
	}
	if(i == len) {
		return false;
	}
}

//获取对应的operator的KEY和VALUE   测试正确 
void getOperator(string ope) {
	int k, i;
	int len = sizeof(operators)/sizeof(string);
	for(i = 0; i < len; i++) {
		k = operators[i].compare(ope);
		if(k == 0) {
			sym = operatorsKey[i];
			value = operators[i];
			break;
		}
	}
	if(i == len) {
		sym = "error";
		value = ope;
	}
}
 
 //测试正确 
bool isResWord(string resWord) {
	int len = sizeof(reservedWord)/sizeof(string);
	int k, i;
	for(i = 0; i < len; i++) {
		k = reservedWord[i].compare(resWord);
		if(k == 0) {
			return true;
		}
	}
	if (i == len) {
		return false;
	}
}

//测试正确 
void getResWord(string resWord) {
	int len = sizeof(reservedWord)/sizeof(string);
	int k, i;
	for(i = 0; i < len; i++) {
		k = reservedWord[i].compare(resWord);
		if(k == 0) {
			sym = reservedWord[i] + "sys";
			value = reservedWord[i];
			break;
		}
	}
	if(i == len) {
		cout << "error" << endl;
	}
}

//判断是哪种类型的界符   测试正确 
 void getBorder(char c) {
	string str;
	str += c;
	int len = sizeof(border)/sizeof(string);
	int k, i;
	for(i = 0; i < len; i++) {
		k = border[i].compare(str);
		if(k == 0) {
			sym = borderKey[i];
			value = border[i];
			break;
		}
	}
	if (i == len) {
		sym = "error";
		value = c;
	}
}

//测试正确 
char getCh() {
	char tmp;
	tmp = buffer[count];	
    count = count + 1;
	return tmp;
}

void getSym() {
	string  A, ID, resWord, num, ope;
	int k;
	while(ch == ' ' || ch == '\n') {
		ch = getCh();
	}
	if(isLetter(ch)) {
		k = 0;
		while((isLetter(ch) || isNumber(ch)) && k < 10) {
		    k++;
			A += ch;	
			ch = getCh();
		}
		ID = A;
		A = ""; 
		if(isResWord(ID)) {
			resWord = ID;
			getResWord(resWord);
		} else {
			sym = "ident";
			value = ID;
		}
	} else {
	    if(isNumber(ch)) {
	    	while(isNumber(ch)) {
	    		num += ch;
			    ch = getCh();
	    	}
            sym = "number";
            value = num;
		} else {
			if (isOperator(ch)) {
				while(isOperator(ch)) {
			        ope += ch;
			        ch = getCh();
		        }
		        getOperator(ope);
		        ope = "";
			} else {
				getBorder(ch);
				ch = getCh();	
			}
		}	
	}	
}

int main() {
	char a;
	int i = 0;
	freopen("test.txt", "r", stdin);
	while(~scanf("%c", &a)) {
		buffer[i] = a;
		i++;
	}
	while(count < i) {
		getSym();
		if(buffer[count - 2] != '\0') {
			cout << sym << ",  " << value << endl;
		}
	}
	return 0;
}
