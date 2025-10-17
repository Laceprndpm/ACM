#include <bits/stdc++.h>

#include <algorithm>
#include <utility>
#include <vector>
#define int long long
using i64 = long long;
using namespace std;
constexpr int INF = 1e9;
#define bg(x)  begin(x)
#define all(x) bg(x), end(x)

template <typename T>
struct Fenwick {
    int       n;
    vector<T> a;

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
};

vector<i64> arr;

struct MinN {
    int pos;

    MinN operator+(const MinN& ot)
    {
        if (arr[pos] < arr[ot.pos]) {
            return *this;
        } else {
            return ot;
        }
    }
};

void solve()
{
    i64 n, m;
    cin >> n >> m;
    arr.resize(n);
    for (i64& i : arr) {
        cin >> i;
    }
    Fenwick<MinN> fk(n);
    for (int i = 0; i < n; i++) {
        fk.add(i, {i});
    }
    vector<pair<i64, i64>> buffer;
    for (int i = 0; i < m; i++) {
        i64 ri, wi;
        cin >> ri >> wi;
        ri--;
        buffer.push_back({ri, wi});
        // auto res = fk.sum(ri);
        // arr[res.pos] -= wi;
    }
    sort(all(buffer));
    for (auto [ri, wi] : buffer) {
        auto res = fk.sum(ri + 1);
        arr[res.pos] -= wi;
        fk.add(res.pos, {res.pos});
    }
    sort(all(arr));
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        ans += arr[i];
        cout << ans << ' ';
    }
    cout << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}