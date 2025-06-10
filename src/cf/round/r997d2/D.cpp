#include <deque>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

template <typename T>
struct Fenwick {
    int            n;
    std::vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{0});
    }

    void add(int x, const T &v)
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

    T rangeSum(int l, int r)
    {
        return sum(r) - sum(l);
    }

    int select(const T &k)
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

template <class T>
struct RangeFenwick {
    int        n;
    Fenwick<T> d1, d2;

    RangeFenwick(int n_) : n(n_), d1(n_), d2(n_) {}

    void add(i64 k, T v)
    {
        T v1 = k * v;
        d1.add(k, v), d2.add(k, v1);
        // 在diff的k位置+v
    }

    void add(i64 l, i64 r, T v)
    {
        add(l, v), add(r, -v);  // 将区间加差分为两个前缀加
    }

    T getsum(i64 x)
    {
        return x * d1.sum(x) - d2.sum(x);
    }

    T getsum(i64 l, i64 r)
    {
        return getsum(r) - getsum(l);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i]--;
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < 10; j++) {
    //         prefix[j][i + 1] += prefix[j][i] + (arr[i] == j);
    //     }
    // }
    // i64                         ans = 0;
    // 如果刚刚好arr[i] == j，那么在下次遇到j前，则不统计答案？
    i64 dans = 0;
    for (int j = 0; j < 10; j++) {
        vector<vector<int>>   brr(2, vector<int>(n * 2 + 50));
        deque<pair<int, int>> dq;
        int                   cnt = 0;
        for (int i = 0; i <= n; i++) {
            dans += brr[i % 2][cnt + n];
            dq.push_back({i % 2, cnt + n});
            if (arr[i] <= j) {
                cnt++;
            } else {
                cnt--;
            }
            if (arr[i] == j) {
                while (!dq.empty()) {
                    auto [idx, val] = dq.front();
                    brr[idx][val]++;
                    dq.pop_front();
                }
            }
        }
    }
    cout << (n + 1) * 1ll * n / 2 - dans << '\n';
}

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 计算以i为r的好区间的数量
    // 拆分成每个数为中位数的贡献
    // 考虑[l,r)，偶数，j是否可以成为中位数
    // k < j 的数量应当小于(r - l) / 2 (>号同理)
    // pre[r] - pre[l] < (r - l) / 2
    // pre[r] - pre[l] + (cnt[r] - cnt[l]) > (r - l) / 2
    //
    //
    // (2 * pre[r] - r) - (2 * pre[l] - l) < 0
    // (2 * pre[r] + cnt[r] - r) - (2 * pre[l] + cnt[l] - l) > 0
    //
    //          (2 * pre[r] - r) < (2 * pre[l] - l)
    // (2 * pre[r] + cnt[r] - r) > (2 * pre[l] + cnt[l] - l)
    //
    //
    // (2 * pre[r] + cnt[r] - r) > (2 * pre[l] + cnt[l] - l) > (2 * pre[l] - l) >  (2 * pre[r] - r)
    //
    //
    //
    //
    // 查找数量
    //
    // 减去不存在中位数的数量
    //
    //
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}