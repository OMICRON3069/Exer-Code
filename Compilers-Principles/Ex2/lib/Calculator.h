//
// Created by aaron on 4/21/18.
//

#ifndef OOO0OOO_CALCULATOR_H
#define OOO0OOO_CALCULATOR_H

#include "Tester.h"
#include "Checker.h"

using namespace std;


bool CalculateFirst(std::vector<CockSucker> &tcs, std::set<char> &FirstSet, char cc) {
    bool SuckerLock = false;
    int count = 0;
    for (auto &it : tcs) {
        string tmp = it.GetRight();
        if (it.GetLeft()[0] == cc) { // Expression match.
            if (!CharacterJudge(tmp[0])) { // If the first one in right side is non end character.
                FirstSet.insert(tmp[0]); //Append this character into FirstSet.
            }
            else {
                for (auto &src : tmp) {
                    if (!CharacterJudge(src)) {
                        FirstSet.insert(src);
                        break;
                    }
                    CalculateFirst(tcs, FirstSet, src);
                    for (auto &ep : FirstSet) {
                        if (ep == '$') {
                            SuckerLock = true;
                            FirstSet.erase('$');
                        }
                    }
                    if (!SuckerLock)
                        break;
                    else {
                        SuckerLock = false;
                        count += 1;
                    }
                }
                if (count == tmp.length()) {
                    FirstSet.insert('$');
                }
            }
        }
    }
    return true;
}

bool CalculateFollow(std::vector<CockSucker> &tcs, std::set<char> &FollowSet, char cc,
                     std::vector<Cunt> &CuntCluster) {
    if (cc==f)
        FollowSet.insert('#');
    for (auto &it : tcs) {
        string tmp = it.GetRight();
        char left = it.GetLeft()[0];
        int Position = -10;

        for (int i = 0; i < tmp.length(); i++) {
            if (tmp[i] == cc) {
                Position = i;
                break;
            }
        }

        if (Position != -10 && Position < tmp.length() - 1) {
            if (!CharacterJudge(tmp[Position + 1])) {
                FollowSet.insert(tmp[Position + 1]);
            }
            else {
                bool EpsilonLock = false;
                for (auto &Check : GetCunt(tmp[Position + 1], CuntCluster).FirstSet) {
                    if (Check == '$') {
                        EpsilonLock = true;
                    }
                    else
                        FollowSet.insert(Check);
                }

                if (EpsilonLock && cc != left)
                    CalculateFollow(tcs,FollowSet,left,CuntCluster);
            }
        }
        else if (Position != -10 && Position == tmp.length()-1 && cc != left) {
            CalculateFollow(tcs,FollowSet,left,CuntCluster);
        }
    }
    return true;
}

bool StartFollow(std::vector<Cunt> &CuntCluster, std::vector<CockSucker> &tcs) {
    for (auto &it : CuntCluster) {
        CalculateFollow(tcs, it.FollowSet, it.B, CuntCluster);
    }
    cout << "-----------------------------------\nFollow Set : \n";
    for (auto &i : CuntCluster) {
        cout << i.B << ":\t";
        for (auto &it : i.FollowSet) {
            cout << it << "\t";
        }
        cout << "\n";
    }
    return true;
}

bool StartFirst(std::set<char> &CuntNo1, std::vector<Cunt> &CuntCluster, std::vector<CockSucker> &tcs) {
    for (auto &it : CuntNo1) {
        CuntCluster.emplace_back(it);
    }

    for (auto &i : CuntCluster) {
        CalculateFirst(tcs, i.FirstSet, i.B);
    }
    /*
     * FirstSet debug info.
     */
    cout << "-----------------------------------\nFirst Set : \n";
    for (auto &i : CuntCluster) {
        cout << i.B << ":\t";
        for (auto &it : i.FirstSet) {
            cout << it << "\t";
        }
        cout << "\n";
    }
    return true;
}

bool GoSelect(std::vector<Cunt> &CuntCluster, std::vector<CockSucker> &tcs,std::set<char> &CuntNo1,
              std::set<char> &CuntNo2, CockSucker cs, int PointerRight, int TableClock) {

    char LeftCha = cs.GetLeft()[0];
    char seek = cs.GetRight()[PointerRight];

    if (!CharacterJudge(seek)) {
        if (seek != '$') {
            TableMap[GetCuntID(LeftCha,CuntNo1)][GetCuntID(seek,CuntNo2)]=TableClock;
        }
        if (seek == '$') {
            for(auto &fit : GetCunt(LeftCha,CuntCluster).FollowSet) {
                TableMap[GetCuntID(LeftCha,CuntNo1)][GetCuntID(fit,CuntNo2)] = TableClock;
            }
        }
    }

    else {
        for (auto &nameless : GetCunt(LeftCha,CuntCluster).FirstSet)
            TableMap[GetCuntID(LeftCha,CuntNo1)][GetCuntID(nameless,CuntNo2)] = TableClock;
        if (GetCunt(LeftCha,CuntCluster).FirstSet.count('$') != 0) {

            if (PointerRight+1 == cs.GetRight().size()) {//stand on border
                for(auto &fit : GetCunt(LeftCha,CuntCluster).FollowSet) {
                    TableMap[GetCuntID(LeftCha,CuntNo1)][GetCuntID(fit,CuntNo2)] = TableClock;
                }
            }
            else {//Go next
                GoSelect(CuntCluster,tcs,CuntNo1,CuntNo2,cs,PointerRight+1,TableClock);
            }
        }
    }
    return true;
}

bool TableGen(std::vector<Cunt> &CuntCluster, std::vector<CockSucker> &tcs,std::set<char> &CuntNo1,
              std::set<char> &CuntNo2) {

    for (auto &i : TableMap) {
        for (int &j : i) {
            j =-1;
        }
    }


    int TableClock = 0;
    for (auto &it : tcs) {

        GoSelect(CuntCluster,tcs,CuntNo1,CuntNo2,it,0,TableClock);

        TableClock++;
    }

    //Debug predict table.
    for (auto &i : CuntNo2) {
        cout << setw(10) << i;
    }
    cout << "\n";
    int count1=0;
    for (auto &i : CuntNo1) {
        cout << i << ": ";
        int count2=0;
        for (auto &j : CuntNo2) {
            if (TableMap[count1][count2] == -1)
                cout << setw(10) << "N/A";
            else
                cout << setw(10) << tcs[TableMap[count1][count2]].GetRight();
            count2++;
        }
        cout << "\n";
        count1++;
    }
    //Debug ended;

    return true;
}


#endif //OOO0OOO_CALCULATOR_H
