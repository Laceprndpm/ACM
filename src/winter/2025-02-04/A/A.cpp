#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void solve()
{
    string sInput;
    cin >> sInput;
    int maxLength    = 0;
    int maxLengthidx = 0;
    int curLength    = 0;
    if (sInput[0] == 'E') {
        maxLengthidx = 0;
        maxLength    = 1;
        curLength++;
    }
    for (int i = 1; i < sInput.size(); i++) {
        if (sInput[i] == 'E') {
            curLength++;
            if (curLength > )
        } else {
            curLength--;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}