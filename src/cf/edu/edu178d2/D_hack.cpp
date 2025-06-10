#include <iostream>
using namespace std;
using i64 = long long;

signed main(int argc, char** argv)
{
    cout << 1 << '\n';
    cout << (i64)4e5 << '\n';
    for (int i = 0; i < (i64)4e5 - 1; i++) {
        cout << 2791458 << ' ';
    }
    cout << 115952 + 2791458 << endl;
    return 0;
}