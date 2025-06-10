#include <cstring>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

int n, p = 1, trie[10000005][26];
i64 ans = 0;

int val[10000005];

void insert(int u, const char* s)
{
    if (!strlen(s)) {
        return;
    }
    if (!trie[u][s[0] - 'a']) {
        trie[u][s[0] - 'a'] = ++p;
        val[p] += 1;
    } else {
        ans += val[trie[u][s[0] - 'a']];
        val[trie[u][s[0] - 'a']]++;
    }
    insert(trie[u][s[0] - 'a'], s + 1);
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
    for (int i = 1; i <= n; i++) {
        string a;
        cin >> a;
        insert(1, a.c_str());
    }
    cout << ans << '\n';
    return 0;
}