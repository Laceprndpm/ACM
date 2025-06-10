// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int>   a(n + 1);
        map<int, int> cnt;
        int           mex = 0, len = n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            cnt[a[i]]++;
        }
        if (cnt[0]) {
            len -= cnt[0] - 1;
            cnt[0] = 1;
        }
        while (cnt[mex])
            mex++;
        bool good = true;
        int  mn   = 1e9;
        for (int i = 1; i <= n; i++) {
            if (--cnt[a[i]] == 0) {
                mex = min(mex, a[i]);
            }
            mn = min(mn, a[i]);
            if (mex > mn)
                good = false;
        }
        cout << len + good - 1 << '\n';
    }
}