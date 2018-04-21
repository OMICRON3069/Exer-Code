//
// Created by omicron3069 on 4/18/2018.
//

#ifndef DING_CHECKER_H
#define DING_CHECKER_H

#include "Tester.h"
using namespace std;

bool IsEndCharacter(int *tmp){
    return !(Buffer[*tmp] >= 'A' || Buffer[*tmp] <= 'Z');
}

bool CuntDuplicationRemove(std::vector<string> &biu) {
    if (biu.size() <= 2)
        return true;
    for (auto it = biu.begin(); it < biu.end(); it++) {
        for (auto itt = it+1 ; itt < biu.end() ; itt ++) {
            if (*itt == *it ) {
                *it = "jibai";
                continue;
            }
        }
    }
    return true;
}

bool CuntGenerator (std::vector<string> &biu,std::vector<Cunt> &CuntCluster) {
    CuntDuplicationRemove(biu);
    for (auto &it : biu) {
        if (it == "jibai") continue;
        else CuntCluster.push_back(Cunt(it));
    }
}

bool GrammarBorderDetecter(int *ite){
    //return Buffer[*ite] != '\n';
    if (Buffer[*ite] != '\n'){
        return false;
    }
    else if (Buffer[*ite] == 0)
        return false;
    else return true;
}

CockSucker::CockSucker(string *src,std::vector<string> &biu) {
    bool LeftLock = true;
    for (auto &it : (*src)) {
        //Check
        //cout << "Test Doc is " << it << "\n";
        if(it == '-' || it == '>'){
            LeftLock = false;
        }
        else if (LeftLock){
            this->Left += it;
            biu.push_back(this->Left);
        }
        else if (!LeftLock){
            this->Right += it;
        }
    }

}

bool CockSucker::Debug() {
    cout << "Debug info " << "\n";
    cout << "Left: " << this->Left << " Right: " << this->Right <<"\n";
}

#endif //DING_CHECKER_H
