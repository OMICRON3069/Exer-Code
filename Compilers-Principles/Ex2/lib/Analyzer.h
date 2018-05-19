//
// Created by aaron on 5/19/18.
//

#ifndef OOO0OOO_ANALYZER_H
#define OOO0OOO_ANALYZER_H

#include "Tester.h"
#include "Checker.h"
using namespace std;

bool Vector2Text(std::vector<char> lPolar, std::vector<char> rPolar) {
    cout <<setw(3)<< BBQ;
    string temp;
    for (auto &it : lPolar){
        if (it=='\n')
            continue;
        temp+=it;
    }
    cout << setw(15) <<temp;
    temp.clear();

    for (auto &it : rPolar){
        if (it=='\n')
            continue;
        temp+=it;
    }
    cout << setw(15) <<temp;
    BBQ++;
    return true;
}

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

    /*
     * --------------------
     * |  lPolar | rPolar |
     * |   #E    |  i+i*i |
     * --------------------
     * */
    delete Buffer,ite;

    while(!rPolar.empty()) {
        //Start !
        if (lPolar.back() == rPolar.front()) {//if stack element match;
            if (Vector2Text(lPolar,rPolar)) {
                char jtemp = lPolar.back();
                lPolar.pop_back();
                rPolar.erase(rPolar.begin());
                if (lPolar.empty() || rPolar.empty()) {
                    cout << setw(15) <<"\tAccept";
                    cout << "\n";
                    break;
                }
                else {
                    cout << setw(15) << jtemp << " Match";
                    cout << "\n";
                }
            }
        }

        else if ( (lPolar.size()==1 && rPolar.size()>=2) || (rPolar.size()==1 && lPolar.size()>=2) ) {//one of two stack is empty
            if (Vector2Text(lPolar,rPolar))
                cout << setw(15) << "Wrong! Incorrect sentence!";
            cout << "\n";
            break;
        }

        else {
            if (GetTableMapValue(lPolar.back(),rPolar.front(),CuntNo1,CuntNo2) == -1) {
                if (Vector2Text(lPolar,rPolar))
                    cout << setw(15) << "Wrong! No table data!";
                cout << "\n";
                break;
            }
            if (Vector2Text(lPolar,rPolar)) {
                cout << setw(15) << GetCockSuckerByID(GetTableMapValue(lPolar.back(),rPolar.front(),CuntNo1,CuntNo2),tcs).GetRight();
                cout << "\n";
            }
            string AppendTemp = GetCockSuckerByID(GetTableMapValue(lPolar.back(),rPolar.front(),CuntNo1,CuntNo2),tcs).GetRight();
            lPolar.pop_back();
            if (AppendTemp == "$")
                continue;
            for (auto i= static_cast<int>(AppendTemp.size() - 1); i>=0;i--) {
                lPolar.push_back(AppendTemp[i]);
            }
        }
    }

    return true;
}


#endif //OOO0OOO_ANALYZER_H
