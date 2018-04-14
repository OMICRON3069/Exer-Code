//
// Created by aaron on 4/13/18.
//
#include <string>

#define MAX 20
using namespace std;
string BorderKey[MAX] = {"comma", "point", "semicolon", "lparen", "rparen", "lbparen", "rbparen"};
string Border[MAX] = {",", ".", ";", "(", ")", "{", "}"};
string ReservedWord[MAX] = {"main", "if", "else", "int", "return", "do", "continue", "break"};
string OperatorsKey[MAX] = {"plus", "sub", "multi", "devide", "pound", "greatOrEqual", "lessOrEqual", "less", "greater", "percent"};
string Operators[MAX] = {"+", "-", "*", "/", "=", ">=", "<=", "<", ">", "%"};
string Sym;
string Value;
char Buffer[1000];
char ch = ' ';
int count = 0;