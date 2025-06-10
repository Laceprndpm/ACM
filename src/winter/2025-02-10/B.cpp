#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

int check(int d, int x)
{
    auto     dig = to_string(d);
    set<int> vis;
    int      trytime = 9;
    while (trytime--) {
        int num = stoi(dig) % x;
        vis.insert(num);
        if (num == 0) {
            return dig.length();
        }
        dig += to_string(d);
    }
    return -1;
}

int jc(int x)
{
    int ans = 1;
    for (int i = x; i > 0; i--) {
        ans *= i;
    }
    return ans;
}

void solve()
{
    int n, d;
    cin >> n >> d;
    for (int i = 1; i <= 9; i += 2) {
        int lenDiv;
        if ((lenDiv = check(d, i)) == -1) {
            continue;
        } else {
            if (n >= lenDiv) {
                cout << i << ' ';
            } else {
                if (jc(n) % lenDiv == 0) {
                    cout << i << ' ';
                }
            }
        }
    }
    cout << '\n';
}

signed main()
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