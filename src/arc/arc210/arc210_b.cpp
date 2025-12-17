#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;
// vectors
#define sz(x)  int(size(x))
#define bg(x)  begin(x)
#define all(x) bg(x), end(x)
#define sor(x) sort(all(x))
#define rsz    resize
#define ins    insert
#define pb     push_back

template <typename T>
struct Fenwick {
    int            n;
    std::vector<T> a;

    Fenwick(int n_ = 0) { init(n_); }

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{});
    }

    void add(int x, const T& v)
    {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }

    T sum(int x)
    {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }

    T rangeSum(int l, int r) { return sum(r) - sum(l); }

    int select(const T& k)
    {
        int x = 0;
        T   cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

void solve()
{
    i64 n, m, q;
    cin >> n >> m >> q;
    Fenwick<i64> numfk(6e5 + 50);
    Fenwick<i64> valfk(6e5 + 50);
    vector<i64>  arr(n + m + 1);
    vector<i64>  val;
    for (int i = 1; i <= n + m; i++) {
        cin >> arr[i];
    }
    vector<array<int, 2>> cmd;
    for (int i = 0; i < q; i++) {
        int ti, qi, xi;
        cin >> ti >> qi >> xi;
        val.pb(xi);
        cmd.pb({qi + (int)(ti == 2 ? n : 0), xi});
    }
    val.ins(val.end(), arr.begin() + 1, arr.end());
    sor(val);
    vector<int> idx(n + m + 1);
    vector<int> offset(val.size());
    auto        newnode = [&](int p, i64 x) {
        int id  = lower_bound(all(val), x) - val.begin();
        int cid = idx[p] = (id + offset[id]++);
        numfk.add(cid, 1);
        valfk.add(cid, x);
    };
    auto replace = [&](int p, i64 x) {
        int rid = idx[p];
        numfk.add(rid, -1);
        valfk.add(rid, -arr[p]);
        arr[p] = x;
        newnode(p, x);
    };
    for (int i = 1; i <= n + m; i++) {
        newnode(i, arr[i]);
    }
    int  k     = n / 2;
    auto query = [&]() {
        int idx1 = numfk.select(k);
        int idx2 = numfk.select(n + m - k);
        i64 res  = valfk.sum(idx1) + valfk.rangeSum(idx2, 6e5 + 50);
        return res;
    };
    for (int i = 0; i < q; i++) {
        replace(cmd[i][0], cmd[i][1]);
        cout << query() << '\n';
    }
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
