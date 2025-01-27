#include <bits/stdc++.h>

#include <stack>
using namespace std;
using LL = long long;

constexpr int N = 1e3 + 5;

char input[N][N];

struct block {
    int l, r, h;
} blocks[N][N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> input[i][j];
        }
    }
    for (int j = 1; j <= m; j++) {
        if (input[1][j] == '.') {
            blocks[1][j].h = 1;
        } else {
            blocks[1][j].h = 0;
        }
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (input[i][j] == '.') {
                blocks[i][j].h = blocks[i - 1][j].h + 1;
            } else {
                blocks[i][j].h = 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        stack<int> mono_s1;
        for (int j = m; j >= 1; j--) {
            while (!mono_s1.empty() && blocks[i][mono_s1.top()].h >= blocks[i][j].h) {
                mono_s1.pop();
            }
            blocks[i][j].r = mono_s1.empty() ? m + 1 : mono_s1.top();
            mono_s1.push(j);
        }
        stack<int> mono_s2;
        for (int j = 1; j <= m; j++) {
            while (!mono_s2.empty() && blocks[i][mono_s2.top()].h > blocks[i][j].h) {
                mono_s2.pop();
            }
            blocks[i][j].l = mono_s2.empty() ? 0 : mono_s2.top();
            mono_s2.push(j);
        }
    }
    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans += (blocks[i][j].r - j) * (j - blocks[i][j].l) * blocks[i][j].h;
        }
    }
    cout << ans;
    return 0;
}