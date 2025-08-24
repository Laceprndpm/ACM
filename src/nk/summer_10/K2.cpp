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

const int N       = 10010;
const int MAX_SUM = 10010;

using ll  = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define endl '\n'

vector<int> g[N], scc[N], g2[N];
int         low[N], dfn[N], idx, cnt;
int         bel[N];
stack<int>  st;
bool        inq[N];

int             val[N], sum[N];
bitset<MAX_SUM> f[N];

void tarjen(int u)
{
    dfn[u] = low[u] = ++idx;
    st.push(u);
    inq[u] = true;

    for (auto v : g[u]) {
        if (!dfn[v]) {
            tarjen(v);
            low[u] = min(low[u], low[v]);
        } else if (inq[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u]) {
        cnt++;
        int v;
        do {
            v = st.top();
            st.pop();
            inq[v] = false;
            bel[v] = cnt;
            scc[cnt].push_back(v);
        } while (v != u);
    }
}

void dfs(int u)
{
    sum[u] = val[u];
    for (int v : g2[u]) {
        dfs(v);
        sum[u] += sum[v];
    }

    f[u].reset();
    f[u][0] = 1;

    for (int v : g2[u]) {
        bitset<MAX_SUM> temp_res;
        for (int k = 0; k < MAX_SUM; ++k) {
            if (f[u][k]) {
                temp_res |= (f[v] << k);
            }
        }
        f[u] = temp_res;
    }

    f[u][sum[u]] = 1;
}

void Uraykevoli()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int         total_sum_a = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        total_sum_a += a[i];
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    int m;
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjen(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        val[bel[i]] += a[i];
    }

    vector<pii> dag_edges;
    vector<int> rd(cnt + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (auto j : g[i]) {
            if (bel[i] != bel[j]) {
                dag_edges.push_back({bel[i], bel[j]});
            }
        }
    }
    sort(dag_edges.begin(), dag_edges.end());
    dag_edges.erase(unique(dag_edges.begin(), dag_edges.end()), dag_edges.end());

    for (auto const& edge : dag_edges) {
        g2[edge.first].push_back(edge.second);
        rd[edge.second]++;
    }

    int root = 0;
    for (int i = 1; i <= cnt; i++) {
        if (rd[i] == 0) {
            root = i;
            break;
        }
    }

    if (root != 0) {
        dfs(root);
        cout << f[root].count() << endl;
    } else {
        if (n == 0)
            cout << 1 << endl;
        else
            cout << f[1].count() << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int _ = 1;
    // cin >> _;
    while (_--) {
        Uraykevoli();
    }

    return 0;
}
