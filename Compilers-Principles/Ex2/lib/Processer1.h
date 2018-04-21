//
// Created by omicron3069 on 4/18/2018.
//

#ifndef DING_PROCESSER1_H
#define DING_PROCESSER1_H

#include "Tester.h"
#include "Checker.h"

using namespace std;

CockSucker GrammarCreator(int *ite,std::vector<string> &biu){
    auto *str = new string;
    while ((!GrammarBorderDetecter(ite)) && (*ite < count) ){
        *str += Buffer[*ite];
        (*ite)++;
    }

    if (GrammarBorderDetecter(ite)) {
        (*ite)++;
    }

    if (!(*str).empty()){
        CockSucker tmp(str,biu);
        tmp.Debug();
        delete str;
        return tmp;
    }
    delete str;
}

bool StartEngine(int *ite){
    /*
     * Load expression.
     */
    if(LoadSrc("expression.txt"))
        cout << "Load successfully" << "\n";

    /*
     * Resolve expression.
     */
    vector<CockSucker> ThisCockSucker;
    vector<Cunt> CuntCluster;
    vector<string> biu;
    while (*ite < count)
        ThisCockSucker.push_back(GrammarCreator(ite,biu));
    //cout << ThisCockSucker.size();

    CuntGenerator(biu,CuntCluster);



    delete Buffer;
    delete ite;
    /*
     * TODO: Load sentence to Buffer here.
     */

}

#endif //DING_PROCESSER1_H
