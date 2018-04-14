#include "../lib/ding.h"
#include "../lib/loader.h"
#include "../lib/checker.h"
#include "../lib/iterators.h"
#include "../lib/getter.h"

/*
 * The Universal error code is 114514!
 */

using namespace std;

int main() {
    string SrcPath="test.txt";

    if(LoadSrc(SrcPath))
        cout << "Load successfully" << "\n";

    ite = 0;

    if (StartIteration())
        return 0;
    else return 114514;
}