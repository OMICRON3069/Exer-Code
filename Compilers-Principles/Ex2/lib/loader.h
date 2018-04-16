//
// Created by omicron3069 on 4/16/2018.
//

#ifndef DING_LOADER_H
#define DING_LOADER_H

#include "tester.h"
#include <fstream>
using namespace std;
//Reuse previously loader function.
bool LoadSrc(string SrcPath){
    ifstream src;
    auto cc = 0;
    count = 0;
    src.open(SrcPath,std::ifstream::in);
    src >> std::noskipws;
    while (!src.eof()){
        src >> Buffer[cc];
        cc++;
        count++;
    }
    src.close();
    count --;
    return true;
}

#endif //DING_LOADER_H
