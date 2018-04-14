//
// Created by aaron on 4/13/18.
//
#include <string>

#define MAX 20
using namespace std;
string BorderKey[MAX] = {"comma", "point", "semicolon", "lparen", "rparen", "lbparen", "rbparen"};
string Border[MAX] = {",", ".", ";", "(", ")", "{", "}"};
string ReservedWord[MAX] = {"main", "if", "else", "int", "return", "do", "continue", "break"};
string OperatorsKey[MAX] = {"plus", "sub", "multi", "division", "equal", "greatOrEqual", "lessOrEqual", "less", "greater", "percent"};
string Operators[MAX] = {"+", "-", "*", "/", "=", ">=", "<=", "<", ">", "%"};
char Buffer[1000];
int count = 0;
int ite = 0;
bool lock = false;
bool NumLock = true;