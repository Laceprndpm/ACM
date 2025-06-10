#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>
using namespace std;
using i64                  = long long;
using PII                  = pair<int, int>;
constexpr int          INF = 1e9;
array<int, 11>         global_sta;
array<vector<int>, 10> global_arr;
array<int, 10>         idx;
i64                    ans = 0;
vector<int>            ansvec;
int                    n;

struct Hash_c {
    Hash_c()
    {
        init();
    };

    static constexpr int N = 200000;

    int tot;

    map<int, int> trie[N];
    int           val[N];

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

    void add(const vector<int>& t)
    {
        int o = 1;
        for (int i = 0; i < n; i++) {
            int& p = trie[o][t[i]];
            if (p == 0) {
                p = newNode();
            }
            o = p;
        }
    }

    int query()
    {
        auto& t = global_sta;
        int   o = 1;
        for (int i = 0; i < n; i++) {
            o = trie[o][t[i]];
        }
        return o;
    }
} h;

void DFS(int cur)
{
    global_sta[cur]--;
    vector<int> vc;
    i64         res = 0;
    for (int i = 0; i < n; i++) {
        vc.push_back(global_arr[i][global_sta[i]]);
        res += global_arr[i][global_sta[i]];
    }
    bool isBan = h.query();
    if (res < ans) {
        global_sta[cur]++;
        return;
    }
    if (!isBan) {
        ans    = res;
        ansvec = vector<int>(global_sta.begin(), global_sta.begin() + n);
        global_sta[cur]++;
        return;
    }
    sort(idx.begin(), idx.begin() + n, [&](int u, int v) {
        return vc[u] > vc[v];
    });
    for (int i = 0; i < n; i++) {
        if (global_sta[idx[i]]) DFS(idx[i]);
    }
    global_sta[cur]++;
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
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ci;
        cin >> ci;
        vector<int> arr(ci);
        global_sta[i] = ci - 1;
        for (int i = 0; i < ci; i++) {
            cin >> arr[i];
        }
        global_arr[i] = std::move(arr);
    }
    iota(idx.begin(), idx.end(), 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        vector<int> pt(n);
        for (int j = 0; j < n; j++) {
            cin >> pt[j];
            pt[j]--;
        }
        h.add(pt);
    }
    DFS(10);
    for (int i = 0; i < n; i++) {
        cout << ansvec[i] + 1 << ' ';
    }
    return 0;
}