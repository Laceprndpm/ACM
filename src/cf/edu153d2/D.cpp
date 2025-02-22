#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

// 看上去只有回文序列是平衡的？回文导致平衡毋庸置疑
// 假如只有一个1，那么平衡必然回文
// 再加一个1。。算了管他呢
// 下次一定看样例
// 1000110
// 11010
// 111000

void solve()
{
    string input;
    cin >> input;
    int l = 0, r = input.length() - 1;
    while (input[l] == input[r] && l < r) {
        l++, r--;
    }
    if (l >= r) {
        cout << "0\n";
        return;
    }
    string substring(input.begin() + l, input.begin() + r + 1);
    {
        int cnt1  = 0;
        int cnt0  = 0;
        int cnt10 = 0;
        int cnt01 = 0;
        for (char i : substring) {
            if (i == '1') {
                cnt1++;
                cnt01 += cnt0;
            } else {
                cnt0++;
                cnt10 += cnt1;
            }
        }
        if (cnt01 == cnt10) {
            cout << "0\n";
            return;
        }
    }
    l = 0, r = substring.length() - 1;
    int losepair = 0;
    while (l < r) {
        if (substring[l] != substring[r]) {
            losepair++;
        }
        l++, r--;
    }
    cout << (losepair + 1) / 2 << '\n';
}

signed main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}