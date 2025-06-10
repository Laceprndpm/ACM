// 如果乱序不在中心，则可以直接得出//对两边分别计数
// 如果乱序在中心
// 如果对[l,r]排序后，s变成回文了
// 除lr外，其他回文。各字母出现的数量与其对应区域相同
// 从两头分别计算，当排序子段的各字母出现次数都大于等于不排序子段的字母出现次数
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

bool compareChar(const vector<int>& x, const vector<int>& y)
{
    for (int i = 0; i < 26; i++) {
        if (x[i] != y[i]) {
            return false;
        }
    }
    return true;
}

bool greatChar(const vector<int>& x, const vector<int>& y)
{
    for (int i = 0; i < 26; i++) {
        if (x[i] < y[i]) {
            return false;
        }
    }
    return true;
}

void solve()
{
    string s;
    cin >> s;
    int l = 0, r = s.size() - 1;
    while (s[l] == s[r] && l < r - 1) {
        l++;
        r--;
    }
    if (l == r - 1) {
        cout << 0 << '\n';
        return;
    }
    string      subs(s.begin() + l, s.begin() + r + 1);
    vector<int> leftS(26);
    vector<int> rightS(26);

    for (int i = 0; i < subs.size() / 2; i++) {
        leftS[subs[i] - 'a']++;
    }
    for (int i = subs.size() / 2; i < subs.size(); i++) {
        rightS[subs[i] - 'a']++;
    }
    if (compareChar(leftS, rightS)) {
        int ml = subs.size() / 2 - 1, mr = subs.size() / 2;
        while (subs[ml] == subs[mr]) {
            ml--;
            mr++;
        }
        cout << subs.size() - mr << '\n';
        return;
    }
    vector<int> totalS(26);
    for (int i = 0; i < 26; i++) {
        totalS[i] = leftS[i] + rightS[i];
    }
    int ansL = 0;
    {
        int         cur = subs.size() / 2;
        vector<int> copyL(leftS);
        vector<int> copyR(rightS);
        while (!greatChar(copyL, copyR)) {
            copyL[subs[cur] - 'a']++;
            copyR[subs[cur] - 'a']--;
            cur++;
        }
        ansL = cur;
    }
    int ansR = 0;
    {
        int         cur = subs.size() / 2 - 1;
        vector<int> copyL(leftS);
        vector<int> copyR(rightS);
        while (!greatChar(copyR, copyL)) {
            copyL[subs[cur] - 'a']--;
            copyR[subs[cur] - 'a']++;
            cur--;
        }
        ansR = subs.size() - cur - 1;
    }
    cout << min(ansL, ansR) << '\n';
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}