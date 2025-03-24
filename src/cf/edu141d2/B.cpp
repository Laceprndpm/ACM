#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

bool check(vector<int> tb, int n)
{
    vector<bool> target(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tb[i * n + j] == 0) {
                return false;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j < n - 1) target[abs(tb[i * n + j] - tb[i * n + j + 1])] = true;
            if (i < n - 1) target[abs(tb[i * n + j] - tb[(i + 1) * n + j])] = true;
        }
    }
    for (int i = 1; i <= n * n - 1; i++) {
        if (!target[i]) {
            return false;
        }
    }
    return true;
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> bd(n, vector<int>(n));
        bd[0][0]   = 1;
        bd[0][1]   = n * n;
        int curval = n * n;
        int delta  = n * n - 2;
        for (int i = 2; i < n * n; i++) {
            int row = i / n;
            int col = i % n;
            if (row % 2 == 1) {
                col = n - col - 1;
            }
            if (i % 2) {
                curval += delta;
            } else {
                curval -= delta;
            }
            delta--;
            bd[row][col] = curval;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << bd[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}

// srand(time(0));
// while (true) {
//     shuffle(tb.begin(), tb.end(), rand());
//     for (int i = 0; i < n; i++) {
//         shuffle(tb[i].begin(), tb[i].end(), rand());
//     }
//     if (check(tb, n)) {
//         for (int i = 0; i < n; i++) {
//             for (int j = 0; j < n; j++) {
//                 cout << tb[i][j];
//             }
//         }
//     }
// }