#include "../lib/ding.h"
#include "../lib/loader.h"
#include "../lib/checker.h"
#include "../lib/iterators.h"
#include "../lib/getter.h"

using namespace std;

int main() {
    string SrcPath="test.txt";

    if(LoadSrc(SrcPath))
        cout << "Load successfully" << "\n";

    if (StartIteration())
        return 0;
    else return 114514;
}