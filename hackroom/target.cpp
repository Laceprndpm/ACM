#include <stdio.h>

#include <algorithm>
#include <bit>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#define int long long
using namespace std;
const int N   = 3e5 + 10;
const int mod = 998244353;
int       a[N];

void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s       = '?' + s;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        a[i] = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') a[++cnt] = max(i - 1, n - i);
    }

    if (cnt <= k) {
        cout << "Alice" << endl;
        return;
    }
    sort(a + 1, a + 1 + cnt, greater<int>());
    //    for(int i=1;i<=cnt;i++)cout<<a[i]<<" ";
    //    cout<<endl;
    if (a[k + 1] >= k)
        cout << "Bob" << endl;
    else
        cout << "Alice" << endl;
}

signed main(signed argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}