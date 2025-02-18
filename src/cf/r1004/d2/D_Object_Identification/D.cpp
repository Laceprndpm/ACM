#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;
array<int, (int)2e5 + 5> aInput;

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> aInput[i];
    }
    int maxIdx = max_element(aInput.begin(), aInput.begin() + n) - aInput.begin();
    int minIdx = min_element(aInput.begin(), aInput.begin() + n) - aInput.begin();
    cout << '?' << ' ' << maxIdx + 1 << ' ' << minIdx << '\n';
    int res;
    cin >> res;
    if (res == 0 || res < aInput[maxIdx] - aInput[minIdx]) {
        cout << '!' << ' ' << 'A' << '\n';
        return;
    }
    if (res > aInput[maxIdx - aInput[minIdx]]) {
        cout << '!' << ' ' << 'B' << '\n';
        return;
    }
    cout << '?' << ' ' << minIdx + 1 << ' ' << maxIdx + 1 << '\n';
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