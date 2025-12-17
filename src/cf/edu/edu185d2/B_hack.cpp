#include <iostream>
using namespace std;

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << 1 << '\n';
    int n = 54772;
    cout << n << '\n';
    for (int i = 1; i <= n; i++) {
        cout << n << " \n"[i == n];
    }
}
