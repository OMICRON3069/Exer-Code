#include "../lib/Tester.h"
#include "../lib/Loader.h"
#include "../lib/Processer1.h"
/*
 * The Universal error code is 114514!
 */


using namespace std;

int main() {
    string SrcPath="test2.txt";

    if(LoadSrc(SrcPath))
        cout << "Load successfully" << "\n";

    auto *ite = new int;
    *ite = 0;

    StartEngine(ite);

    delete ite;
    return 0;
}