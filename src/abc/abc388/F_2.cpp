#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

// vectors
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

constexpr int INF = 1e9;

template <class T>
struct Matrix {
    vector<vector<T>> data;

    constexpr Matrix(const vector<vector<T>> &o)
    {
        this->data = o;
    }

    friend constexpr Matrix operator*(const Matrix &lhs, const Matrix &rhs)
    {
        assert(lhs.data[0].size() == rhs.data.size());
        int               n = lhs.data.size(), p = lhs.data[0].size(), m = rhs.data[0].size();
        vector<vector<T>> res(n, vector<T>(m));
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < p; k++) {
                for (int j = 0; j < m; j++) {
                    res[i][j] += lhs.data[i][k] * rhs.data[k][j];
                }
            }
        }
        return {res};
    }

    constexpr Matrix operator*=(const Matrix &o) &
    {
        *this = *this * o;
        return *this;
    }
};

struct BoolWrap {
    bool data = 0;

    friend BoolWrap operator*(BoolWrap a, BoolWrap b)
    {
        return {(a.data && b.data)};
    }

    BoolWrap operator+=(const BoolWrap &o) &
    {
        this->data = this->data || o.data;
        return *this;
    }
};

signed main(signed argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    vector<vector<BoolWrap>> shift_(21, vector<BoolWrap>(21));
    i64                      n, m, a, b;
    cin >> n >> m >> a >> b;
    for (int i = 0; i < 20; i++) {
        shift_[i + 1][i] = {1};
    }
    auto forward_dp_ = shift_;
    for (int i = 20 - b + 1; i <= 20 - a + 1; i++) {
        forward_dp_[i][20] = {1};
    }
    vector<vector<BoolWrap>> now  = vector<vector<BoolWrap>>(1, vector<BoolWrap>(21));
    now[0][20]                    = {1};
    Matrix<BoolWrap>        start = now, shift = shift_, forward_dp = forward_dp_;
    vector<decltype(shift)> fac_shift, fac_dp;
    fac_shift.pb(shift);
    fac_dp.pb(forward_dp);
    for (int i = 0; i < 60; i++) {
        fac_shift.pb(fac_shift.bk * fac_shift.bk);
        fac_dp.pb(fac_dp.bk * fac_dp.bk);
    }
    auto fsp = [&](i64 steps) -> void {
        int weight = 0;
        while (steps) {
            if (steps & 1) {
                start = start * fac_dp[weight];
            }
            weight++;
            steps >>= 1;
        }
    };
    auto fsp0 = [&](i64 steps) -> void {
        int weight = 0;
        while (steps) {
            if (steps & 1) {
                start = start * fac_shift[weight];
            }
            weight++;
            steps >>= 1;
        }
    };
    i64 cur = 1;
    for (int i = 0; i < m; i++) {
        i64 l, r;
        cin >> l >> r;
        if (l == 1) {
            cout << "No\n";
            return 0;
        }
        assert(cur < l);
        fsp(l - cur - 1);
        cur = l - 1;
        fsp0(r - cur);
        cur = r;
    }
    assert(cur <= n);
    fsp(n - cur);
    if (start.data[0][20].data) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */