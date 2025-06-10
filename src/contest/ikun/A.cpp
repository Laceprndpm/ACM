#include <algorithm>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct node {
    int         idx;
    int         star;
    vector<int> arr;
    i64         sum = 0;

    bool operator<(node& t)
    {
        if (star != t.star) return star < t.star;
        return sum < t.sum;
    };

    void flushSum(void)
    {
        sum = 0;
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] != -1) {
                sum += arr[i];
            }
        }
    }
};

void solve()
{
    i64 n, m, k;
    cin >> n >> m >> k;
    vector<node> save(n + 1, node{1, 0, vector<int>(m + 1)});
    for (int i = 1; i <= n; i++) {
        node& n = save[i];
        n.idx   = i;
        cin >> n.star;
        for (int j = 1; j <= m; j++) {
            cin >> n.arr[j];
        }
        n.flushSum();
    }
    sort(save.begin() + 1, save.begin() + 1 + n);
    i64 lastsum  = -1;
    i64 lastStar = 0;
    for (int i = 1; i <= n; i++) {
        node& cur = save[i];
        i64   need;
        if (cur.star > lastStar)
            need = max(lastsum - cur.sum + 1, 0ll);
        else {
            need = max(lastsum - cur.sum, 0ll);
        }
        for (int j = 1; j <= m; j++) {
            if (cur.arr[j] == -1) {
                i64 delta = min(k, need);
                need -= delta;
                cur.arr[j] = delta;
                cur.sum += delta;
            }
        }
        if ((cur.sum == lastsum && cur.star != lastStar) || (cur.sum < lastsum)) {
            cout << "No\n";
            return;
        }
        lastStar = cur.star;
        lastsum  = cur.sum;
    }
    cout << "Yes\n";
    sort(save.begin() + 1, save.begin() + 1 + n, [](const node& a, const node& b) {
        return a.idx < b.idx;
    });
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << save[i].arr[j] << ' ';
        }
        cout << '\n';
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}