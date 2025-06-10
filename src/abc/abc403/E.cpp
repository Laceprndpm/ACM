#include <cstring>
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
constexpr int N   = 500005;

int tot;

int  trie[N][26];
int  val[N];
bool hasPre[N];

int newNode()
{
    int x = ++tot;
    memset(trie[x], 0, 26 * sizeof(int));
    val[x] = 0;
    return x;
}

void init()
{
    tot = 0;
    newNode();
}

void addY(string x, int t)
{
    int o = 1;
    for (int i = 0; i < x.length(); i++) {
        int& p = trie[o][x[i] - 'a'];
        if (!p) {
            p = newNode();
        }
        o = p;
        val[o] += t;
    }
}

void addX(string x)
{
    int o = 1;
    for (int i = 0; i < x.length(); i++) {
        int& p = trie[o][x[i] - 'a'];
        if (!p) {
            p = newNode();
        }
        o = p;
    }
    hasPre[o] = true;
}

bool queryPre(string x)
{
    int o = 1;
    for (int i = 0; i < x.length(); i++) {
        if (trie[o][x[i] - 'a'] != 0) {
            o = trie[o][x[i] - 'a'];
        } else {
            return false;
        }
        if (hasPre[o]) {
            return true;
        }
    }
    return false;
}

int queryPreVal(string x)
{
    int o   = 1;
    int ans = 0;
    for (int i = 0; i < x.length(); i++) {
        if (trie[o][x[i] - 'a'] != 0) {
            o = trie[o][x[i] - 'a'];
        } else {
            return 0;
        }
    }
    ans = val[o];
    o   = 1;
    for (int i = 0; i < x.length(); i++) {
        o = trie[o][x[i] - 'a'];
        val[o] -= ans;
    }
    return ans;
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
    i64 ans = 0;
    init();
    for (int i = 0; i < n; i++) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            string x;
            cin >> x;
            if (!queryPre(x)) {
                ans -= queryPreVal(x);
                addX(x);
            }
        } else {
            string x;
            cin >> x;
            if (!queryPre(x)) {
                ans++;
                addY(x, 1);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}