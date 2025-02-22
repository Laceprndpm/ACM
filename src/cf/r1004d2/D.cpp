#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;
array<int, (int)2e5 + 5> aInput;

void solve()
{
    int n;
    cin >> n;
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> aInput[i];
        cnt[aInput[i]]++;
    }
    int mex = 1;
    while (cnt[mex]) {
        mex++;
    }
    if (mex == n + 1) {
        int a = find(aInput.begin(), aInput.end(), 1) - aInput.begin() + 1;
        int b = find(aInput.begin(), aInput.end(), n) - aInput.begin() + 1;
        cout << '?' << ' ' << a << ' ' << b << endl;
        int res;
        cin >> res;
        if (res > n - 1) {
            cout << '!' << ' ' << 'B' << endl;
            return;
        }
        if (res == 0 || res < n - 1) {
            cout << '!' << ' ' << 'A' << endl;
            return;
        }
        cout << '?' << ' ' << b << ' ' << a << endl;
        cin >> res;
        if (res == n - 1) {
            cout << '!' << ' ' << 'B' << endl;
            return;
        } else {
            cout << '!' << ' ' << 'A' << endl;
            return;
        }
    } else {
        cout << '?' << ' ' << mex << ' ' << (mex == 1 ? 2 : 1) << endl;
        int res;
        cin >> res;
        if (res == 0) {
            cout << '!' << ' ' << 'A' << endl;
        } else {
            cout << '!' << ' ' << 'B' << endl;
        }
    }
}

signed main(int argc, char** argv)
{
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}