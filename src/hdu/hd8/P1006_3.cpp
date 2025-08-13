#include <algorithm>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
const int N = 2e6 + 10;
using ll    = long long;
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define endl '\n'
#define ls   (k + k)
#define rs   (k + k + 1)

struct node {
    int sum[4][4];
    int L, R;

    node()
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                sum[i][j] = -1;
        }
    }

    void clear()
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                sum[i][j] = -1;
            }
        }
    }
} f[N];

int a[N];

node update(const node& l, const node& r)
{
    node res;
    int  L = l.L, R = r.R;
    res.L = L, res.R = R;
    int len = R - L + 1;
    if (len == 2) {
        res.sum[0][0] = 0;
        res.sum[1][0] = a[L];
        res.sum[0][1] = a[R];
        res.sum[2][2] = a[L] + a[R];
    } else if (len == 3) {
        res.sum[0][0] = a[L + 1];
        res.sum[0][1] = a[R];
        res.sum[0][2] = a[R] + a[R - 1];
        res.sum[1][0] = a[L];
        res.sum[1][1] = a[L] + a[R];
        res.sum[2][0] = a[L] + a[L + 1];
        res.sum[3][3] = a[L] + a[L + 1] + a[R];
    } else if (len == 4) {
        res.sum[0][0] = a[L + 1] + a[L + 2];
        res.sum[0][1] = a[L + 1] + a[R];
        res.sum[0][2] = a[L + 2] + a[L + 3];
        res.sum[0][3] = a[L + 1] + a[L + 2] + a[L + 3];
        res.sum[1][0] = a[L] + a[L + 2];
        res.sum[1][1] = a[L] + a[R];
        res.sum[1][2] = a[L] + a[L + 2] + a[R];
        res.sum[2][0] = a[L] + a[L + 1];
        res.sum[2][1] = a[L] + a[L + 1] + a[R];
        res.sum[3][0] = a[L] + a[L + 1] + a[L + 2];
    } else if (len == 5) {
        res.sum[0][0] = a[L + 1] + a[L + 2] + a[L + 3];
        res.sum[0][1] = a[L + 1] + a[L + 2] + a[R];
        res.sum[0][2] = a[L + 1] + a[R] + a[R - 1];
        res.sum[0][3] = a[R] + a[R - 1] + a[R - 2];
        res.sum[1][0] = a[L] + a[L + 2] + a[R - 1];
        res.sum[1][1] = a[L] + a[L + 2] + a[R];
        res.sum[1][2] = a[L] + a[R] + a[R - 1];
        res.sum[1][3] = a[L] + a[R] + a[R - 1] + a[R - 2];
        res.sum[2][0] = a[L] + a[L + 1] + a[R - 1];
        res.sum[2][1] = a[L] + a[L + 1] + a[R];
        res.sum[2][2] = a[L] + a[L + 1] + a[R] + a[R - 1];
        res.sum[3][0] = a[L] + a[L + 1] + a[L + 2];
        res.sum[3][1] = a[L] + a[L + 1] + a[L + 2] + a[R];
    } else if (len == 6) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int x = 0; x < 4; x++) {
                    for (int y = 0; y <= 3 - x; y++) {
                        if (x == 3 && y == 3) continue;
                        if (l.sum[i][x] != -1 && r.sum[y][j] != -1)
                            res.sum[i][j] = max(res.sum[i][j], l.sum[i][x] + r.sum[y][j]);
                    }
                }
            }
        }
    } else {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int x = 0; x < 4; x++) {
                    for (int y = 0; y <= 3 - x; y++) {
                        if (l.sum[i][x] != -1 && r.sum[y][j] != -1)
                            res.sum[i][j] = max(res.sum[i][j], l.sum[i][x] + r.sum[y][j]);
                    }
                }
            }
        }
    }
    return res;
}

void build(int k, int l, int r)
{
    f[k].clear();
    if (l == r) {
        f[k].L = f[k].R = l;
        f[k].sum[0][0]  = 0;
        f[k].sum[1][1]  = a[l];
        return;
    }
    int m = (l + r) >> 1;
    build(ls, l, m);
    build(rs, m + 1, r);
    f[k] = update(f[ls], f[rs]);
}

int get(const node& x)
{
    int ans = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i + j > 3) continue;

            ans = max(ans, x.sum[i][j]);
        }
    }
    return ans;
}

void change(int k, int l, int r, int pos, int val)
{
    if (l == r) {
        f[k].sum[0][0] = 0;
        f[k].sum[1][1] = val;
        return;
    }
    int m = (l + r) >> 1;
    if (pos <= m)
        change(ls, l, m, pos, val);
    else
        change(rs, m + 1, r, pos, val);
    f[k] = update(f[ls], f[rs]);
}

void Uraykevoli()
{
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    cout << get(f[1]) << endl;
    while (q--) {
        int pos, val;
        cin >> pos >> val;
        a[pos] = val;
        change(1, 1, n, pos, val);
        cout << get(f[1]) << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--)
        Uraykevoli();
    // return 0;
}

/*
1
6 10
2 2 2 2 2 2
*/
