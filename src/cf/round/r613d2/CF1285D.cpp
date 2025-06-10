#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
constexpr int N   = 200000 * 31;
/**
 * @Spell : DFS, Tire
 */
int tot;

int trie[N][2];
int val[N];

int newNode()
{
    int x      = ++tot;
    trie[x][0] = trie[x][1] = 0;
    val[x]                  = 0;
    return x;
}

void init()
{
    tot = 0;
    newNode();
}

void add(int x)
{
    int o = 1;
    for (int i = 29; i >= 0; i--) {
        int& p = trie[o][x >> i & 1];
        if (!p) {
            p = newNode();
        }
        o = p;
        // val[o] += t;
    }
}

int dfs(int o, int i, int val)
{
    if (i == -1) {
        return val;
    }
    if (trie[o][1] && trie[o][0]) {
        val |= 1 << i;
        return min(dfs(trie[o][1], i - 1, val), dfs(trie[o][0], i - 1, val));
    }
    if (trie[o][1] && !trie[o][0]) {
        return dfs(trie[o][1], i - 1, val);
    } else {
        return dfs(trie[o][0], i - 1, val);
    }
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
    int n;
    cin >> n;
    init();
    for (int i = 0; i < n; i++) {
        int u;
        cin >> u;
        add(u);
    }
    cout << dfs(1, 29, 0);
    return 0;
}