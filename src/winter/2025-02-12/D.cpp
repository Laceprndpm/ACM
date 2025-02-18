#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

constexpr int MAXN = 2e5 + 5;

int x_input[MAXN];

signed main()
{
    srand(time(0));
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> x_input[i];
        }
        int t1, t2;
        t1 = rand() % n + 1;
        t2 = rand() % n + 1;
        while (t2 == t1) {
            t2 = rand() % n + 1;
        }
        cout << '?' << ' ' << x_input[t1] << ' ' << x_input[t2] << endl;

        int q1;
        cin >> q1;
        cout << '?' << ' ' << x_input[t2] << ' ' << x_input[t1] << endl;
        int q2;
        cin >> q2;
        if (q1 != q2 || q1 == 0 || q2 == 0) {
            cout << "! A" << endl;
        } else {
            cout << "! B" << endl;
        }
    }
    return 0;
}