#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    LL l, r;
    cin >> l >> r;
    vector<array<LL, 2>> ans;
    while (l < r) {
        LL p2 = 1;
        LL bl = l;
        while (bl % 2 == 0 && l + p2 <= r) {
            bl >>= 1;
            p2 <<= 1;
        }
        while (l + p2 > r) {
            p2 >>= 1;
            bl <<= 1;
        }
        ans.push_back({l, l + p2});
        l += p2;
    }
    cout << ans.size() << '\n';
    for (auto& i : ans) {
        cout << i[0] << ' ' << i[1] << '\n';
    }

    return 0;
}
