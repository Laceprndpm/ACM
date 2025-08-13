#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int SG_path(int k)
{
    if (k == 0) return 0;
    return (k + 1) / 2;
}

int SG_cycle(int k)
{
    if (k == 1) return 1;
    if (k == 2) return 1;
    if (k == 3) return 0;
    return SG_path(k - 3);
}

void solve()
{
    int n;
    cin >> n;
    int total = 0;
    for (int i = 0; i < n; i++) {
        int num, path;
        cin >> num >> path;
        if (path == 1) {  // path
            total ^= SG_path(num);
        } else {  // cycle
            total ^= SG_cycle(num);
        }
    }
    if (total != 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}