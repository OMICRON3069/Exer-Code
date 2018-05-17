//
// Created by omicron3069 on 4/18/2018.
//

#ifndef DING_PROCESSER1_H
#define DING_PROCESSER1_H

#include "Tester.h"
#include "Checker.h"
#include "Calculator.h"

using namespace std;

CockSucker GrammarCreator(int *ite) {
    auto *str = new string;
    while ((!GrammarBorderDetector(ite)) && (*ite < count)) {
        *str += Buffer[*ite];
        (*ite)++;
    }

    if (GrammarBorderDetector(ite)) {
        (*ite)++;
    }

    if (!(*str).empty()) {
        CockSucker tmp(str);
        tmp.Debug();
        delete str;
        return tmp;
    }
    delete str;
}

int **CockSucker::TableMap;
bool StartEngine(int *ite) {
    /*
     * Load expression.
     */
    if (LoadSrc("expression.txt"))
        cout << "Load expression successfully\n\n";



    /*
     * Resolve expression.
     */
    vector<CockSucker> ThisCockSucker;
    while (*ite < count)
        ThisCockSucker.push_back(GrammarCreator(ite));
    //cout << ThisCockSucker.size();

    delete Buffer;
    delete ite;

    set<char> CuntNo1; //Non-Terminal character. eg:'E'.
    set<char> CuntNo2; // Terminal character. eg:'e'.

    CuntGenerator(CuntNo1, CuntNo2, ThisCockSucker);

    vector<Cunt> CuntCluster;

    if (StartFirst(CuntNo1, CuntCluster, ThisCockSucker))
        cout << "First set calculated successfully\n\n";

    if (StartFollow(CuntCluster, ThisCockSucker))
        cout << "Follow set calculated successfully\n\n";


    /*
     * TODO: Load sentence to Buffer here.
     */

    if (LoadSrc("sentence.txt"))
        cout << "Load sentence successfully\n\n";



    TableGen(CuntCluster,ThisCockSucker,CockSucker::TableMap,CuntNo1,CuntNo2);


    for (int i=0;i<CuntNo1.size();i++) {
        for (int j=0;j<CuntNo2.size();j++) {
            cout<<CockSucker::TableMap[i][j];
        }
        cout<<"\n";
    }

    //clean up TableMap;
    /*hide this because some error
    for (int i=0;i<CuntNo1.size();i++)
        delete[] CockSucker::TableMap[i];
    delete[] CockSucker::TableMap;
    */
    return true;
}

#endif //DING_PROCESSER1_H
