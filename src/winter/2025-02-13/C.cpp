#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;
LL X0, Y0, R;

LL qpow(LL n, LL q)
{
    if (n < 0) {
        n = -n;
    }
    if (q == 0) {
        return 1;
    }
    LL ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
        }
        n *= n;
        q >>= 1;
    }
    return ans;
}

int check(LL x, LL y)
{
    return ((qpow(x - X0, 2) + qpow(y - Y0, 2) > qpow(R, 2)) ? 1 : 0);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> X0 >> Y0 >> R;
    int N;
    cin >> N;
    map<string, int> lol;
    while (N--) {
        LL     x, y;
        string name;
        cin >> x >> y >> name;
        lol[name] += check(x, y);
    }
    LL ans = 0;
    for (auto iter : lol) {
        if (iter.second == 0) {
            ans++;
        }
    }
    cout << ans << '\n';
    LL cur = 0;
    for (auto iter : lol) {
        if (iter.second == 0) {
            if (cur < ans - 1) {
                cout << iter.first << ' ';
                cur++;
            } else {
                cout << iter.first;
            }
        }
    }
    cout << endl;
    return 0;
}
