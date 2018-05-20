//
// Created by aaron on 5/10/18.
//

#ifndef OOO0OOO_POLISH_H
#define OOO0OOO_POLISH_H

#include "Tester.h"

using namespace std;

bool ischarator(char b) {
    return b >= 'a' && b <= 'z';
}

int GetPriority (char b) {
    /*
     * +----------+----------+
       | Operator | Priority |
       +----------+----------+
       | +        |        1 |
       | -        |        1 |
       | x        |        2 |
       | /        |        2 |
       +----------+----------+

     * */
    switch (b) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        default:  return 0;
    }
}

bool LastJob(std::vector<char> Polar) {
    if (Polar.back() == '#')
        Polar.pop_back();

    vector<char> OpStack; //init operator stack(fake);

    while (!Polar.empty() && !OpStack.empty()) {

    }
    return true;
}

#endif //OOO0OOO_POLISH_H
