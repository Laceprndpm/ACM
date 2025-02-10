#include <bits/stdc++.h>
using namespace std;
#define LL long long
map<LL, LL> g;
set<LL>     s;

int main(int argc, char** argv)
{
#ifndef ONLINE_JUDGE
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    LL n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        LL x;
        cin >> x;
        s.insert(x);
        g[x]++;
    }
    int m;
    cin >> m;
    LL lastans = 0;
    for (int i = 1; i <= m; i++) {
        LL x;
        cin >> x;
        x ^= lastans;
        auto it = s.lower_bound(x - k);
        while (it != s.end() && *it <= x + k) {
            lastans += g[*it];
            it = s.erase(it);
        }
        cout << lastans << endl;
    }
    return 0;
}