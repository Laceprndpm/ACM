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

int ans = 10;

bool check(const string& substring)
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
        return true;
    } else {
        return false;
    }
}

int DFS(string& s, int operateTimes)
{
    int sLength = s.length();
    if (operateTimes >= ans) {
        return ans;
    }
    if (check(s)) {
        ans = operateTimes;
        return operateTimes;
    }
    for (int i = 0; i < sLength - 1; i++) {
        for (int j = i + 1; j < sLength; j++) {
            if (s[i] != s[j]) {
                swap(s[i], s[j]);
                DFS(s, operateTimes + 1);
                swap(s[i], s[j]);
            }
        }
    }
    return ans;
}

void solve()
{
    string input;
    cin >> input;
    DFS(input, 0);
    cout << ans;
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