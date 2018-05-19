//
// Created by aaron on 5/19/18.
//

#ifndef OOO0OOO_ANALYZER_H
#define OOO0OOO_ANALYZER_H

#include "Tester.h"
using namespace std;

bool Buffer2Vector(int *ite,std::vector<char> &Polar) {
    while (*ite < count) {
        Polar.push_back(Buffer[*ite]);
        (*ite)++;
    }
    return true;
}

bool AnalyzeSentence(int *ite,std::vector<char> &Polar) {
    ite = new int(0);
    if (!Buffer2Vector(ite,Polar)) {
        cout << "error while convert sentence\n";
        exit(0);
    }

    delete Buffer,ite;



    return true;
}


#endif //OOO0OOO_ANALYZER_H
