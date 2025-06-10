#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
int           n;

void change(int u)
{
    cout << "? 2 " << u << endl;
}

i64 query(const vector<int>& q)
{
    cout << "? 1 " << q.size() << ' ';
    for (int i : q) {
        cout << i << ' ';
    }
    cout << endl;
    i64 res;
    cin >> res;
    cin.clear();
    return res;
}

int rt;

void findRoot()
{
    vector<int> candi;
    for (int i = 2; i <= n; i++) {
        candi.push_back(i);
    }

    int cur = query(candi);
    change(1);
    if (abs(cur - query(candi)) == (n - 1) * 2) {
        rt = 1;
        return;
    }

    while (true) {
        if (candi.size() == 1) {
            break;
        }
        i64         sz   = candi.size();
        i64         half = sz / 2;
        vector<int> l(candi.begin(), candi.begin() + half), r(candi.begin() + half, candi.end());
        i64         res1 = query(l);
        change(1);
        i64 res2 = query(l);
        if (abs(res1 - res2) == half * 2) {
            candi = r;
        } else {
            candi = l;
        }
    }
    assert(!candi.empty());
    rt = candi[0];
    assert(rt == 2);
}

void work()
{
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        arr[i] = query({i});
    }
    if (rt == 1) {
        for (int i = 2; i <= n; i++) {
            arr[i] -= arr[1];
        }
    } else {
        for (int i = 2; i <= n; i++) {
            if (i == rt) continue;
            arr[i] = arr[i] - arr[1];
        }
        arr[1] = arr[1] - arr[rt];
    }
    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

void solve()
{
    cin >> n;
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    findRoot();
    work();
}

signed main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}