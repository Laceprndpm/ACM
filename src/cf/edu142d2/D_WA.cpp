#include <bits/stdc++.h>
using namespace std;
using i64               = long long;
using PII               = pair<int, int>;
constexpr int       INF = INT32_MAX;
int                 p   = 1, trie[205005][11];
int                 n, m;
vector<vector<int>> board(5e4 + 50, vector<int>(11));
int                 buffer[11];

int init()
{
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}

void print(int x)
{
    if (x < 0) x = -x, putchar('-');
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

void insert(int u, const vector<int>& s)
{
    for (int i = 1; i <= m; i++) {
        buffer[s[i]] = i;
    }
    int place = 1;
    while (place <= m) {
        if (!trie[u][buffer[place]]) trie[u][buffer[place]] = ++p;
        u = trie[u][buffer[place]];
        place++;
    }
}

int calcsize(const vector<int>& s)
{
    int p = 1;
    for (int i = 1; i <= m; i++) {
        if (trie[p][s[i]] == 0) return i - 1;
        p = trie[p][s[i]];
    }
    return m;
}

void solve()
{
    n = init(), m = init();
    memset(trie, 0, sizeof(int) * 11 * (p + 5));
    p = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            board[i][j] = init();
        }
        insert(1, board[i]);
    }
    for (int i = 1; i <= n; i++) {
        print(calcsize(board[i]));
        putchar(' ');
    }
    putchar('\n');
}

signed main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    t = init();
    while (t--) {
        solve();
    }
    return 0;
}

// vector<int> res = mul(board[1], board[2]);
// for (int i = 1; i <= m; i++) {
//     cout << res[i] << ' ';
// }

// vector<int> mul(vector<int> p, vector<int> q)
// {
//     int         n = p.size() - 1;
//     vector<int> ans(p.size());
//     for (int i = 1; i <= n; i++) {
//         ans[i] = q[p[i]];
//     }
//     return ans;
// }

// 2 4 1 3
// 考虑 p = 2 4 1 3
// q的第二个最好是1，第四个最好是2.。。
// 或者说q的1最好在第二位，2最好在第四位。。。
// 字典树！
// vector<int> reve(const vector<int>& s)
// {
//     vector<int> ans(m + 1);
//     for (int i = 1; i <= m; i++) {
//         ans[s[i]] = i;
//     }
//     return ans;
// }

// void insert(int u, const vector<int>& s, int place)
// {
//     if (place == m + 1) {
//         return;
//     }
//     if (!trie[u][s[place]]) trie[u][s[place]] = ++p;
//     insert(trie[u][s[place]], s, place + 1);
// }
