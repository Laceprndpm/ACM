#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        string s;
        cin >> s;
        if (find(s.begin(), s.end(), '7') - find(s.begin(), s.end(), '3') > 0)
            cout << 37 << '\n';
        else {
            cout << 73 << '\n';
        }
    }
    return 0;
}