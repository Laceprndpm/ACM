#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    string A;
    string B;
    cin >> A >> B;
    for (int i = 0; i < A.size() - 1; i++) {
        if (A[i] == '0' && B[i] == '0' && A[i + 1] == '1' && B[i + 1] == '1') {
            cout << "YES" << '\n';
            return;
        }
    }
    cout << "NO" << '\n';
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