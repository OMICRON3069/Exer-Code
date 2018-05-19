//
// Created by aaron on 5/19/18.
//

#ifndef OOO0OOO_ANALYZER_H
#define OOO0OOO_ANALYZER_H

#include "Tester.h"
#include "Checker.h"
using namespace std;

bool Buffer2Vector(int *ite,std::vector<char> &Polar) {
    while (*ite < count) {
        Polar.push_back(Buffer[*ite]);
        (*ite)++;
    }
    return true;
}

bool AnalyzeSentence(int *ite,std::vector<char> &rPolar, std::vector<CockSucker> &tcs, std::vector<Cunt> &CuntCluster,
                     std::set<char> &CuntNo1, std::set<char> &CuntNo2) {
    ite = new int(0);
    if (!Buffer2Vector(ite,rPolar)) {
        cout << "error while convert sentence\n";
        exit(0);
    }

    vector<char> lPolar;
    lPolar.push_back('#');
    lPolar.push_back(tcs[0].GetLeft()[0]);

    delete Buffer,ite;



    return true;
}


#endif //OOO0OOO_ANALYZER_H
