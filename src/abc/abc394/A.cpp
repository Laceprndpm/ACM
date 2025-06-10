#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> s;
    string ans;
    for (char& i : s) {
        if (i == '2') {
            ans += "2";
        }
    }
    cout << ans;
    return 0;
}