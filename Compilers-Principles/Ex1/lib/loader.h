//
// Created by aaron on 4/13/18.
//
//Load program from file.

#ifndef DING_LOADER_H
#define DING_LOADER_H

#include "ding.h"
#include <fstream>

using namespace std;

bool LoadSrc(string SrcPath){
    ifstream src;
    auto cc = 0;
    count = 0;
    src.open(SrcPath,std::ifstream::in);
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
