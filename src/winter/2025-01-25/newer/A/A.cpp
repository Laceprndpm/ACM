#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int init() {
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}

void print(int x) {
    if (x < 0)
        x = -x, putchar('-');
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}

struct node {
    int a;
    int b;
    int diff;
    int idx;

    bool operator<(node &other) {
        return this->diff < other.diff;
    }
} diff[50050];

int n, m;
LL  frontsum[50055];
LL  backsum[50055];
LL  frontsumDiff[50055];

LL findMinimum(LL (*f)(LL), int a, int b) {
    while (a < b) {
        int mid = a + (b - a) / 2;
        if (f(mid) > f(mid + 1)) {
            a = mid + 1;
        } else {
            b = mid;
        }
    }
    return a;
}

LL helpFunction(LL i) {
    LL cur = frontsum[i] - frontsum[0];                // [1, i]
    cur += backsum[n - m + i + 1] - backsum[n + 1];    // [n - m + i + 1, n]
    cur += frontsumDiff[n - m + i] - frontsumDiff[i];  // (i, n - m + i]}
    return cur;
}

void solve(void) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        diff[i].a   = init();
        diff[i].idx = i;
    }
    for (int i = 1; i <= n; i++) {
        diff[i].b    = init();
        diff[i].diff = diff[i].a - diff[i].b;
    }
    sort(diff + 1, diff + 1 + n);
    for (int i = 1; i <= n; i++) {
        frontsum[i] = frontsum[i - 1] + max(0, diff[i].diff);
    }

    backsum[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        backsum[i] = backsum[i + 1] + max(0, -diff[i].diff);
    }

    for (int i = 1; i <= n; i++) {
        frontsumDiff[i] = frontsumDiff[i - 1] + abs(diff[i].diff);
    }

    // LL  min_cur = LLONG_MAX;
    int min_idx = 0;
    // for (int i = 0; i <= m; i++) {
    //     LL cur = helpFunction(i);
    //     if (cur < min_cur) {
    //         min_cur = cur;
    //         min_idx = i;
    //     }
    // }
    min_idx = findMinimum(helpFunction, 0, m);
    vector<int> PorA(n + 1, 0);
    for (int i = 1; i <= min_idx; i++) {
        PorA[diff[i].idx] = -1;
    }

    for (int i = n - m + min_idx + 1; i <= n; i++) {
        PorA[diff[i].idx] = 1;
    }

    for (int i = 1; i <= n; i++) {
        print(PorA[i]);
        cout << ' ';
    }
    cout << '\n';
    return;
}

signed main(int argc, char **argv) {
// #ifndef ONLINE_JUDGE
//     freopen(argv[1], "r", stdin);
//     freopen(argv[2], "w", stdout);
// #endif
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}