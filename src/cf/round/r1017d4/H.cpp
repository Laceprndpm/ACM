#include <bits/stdc++.h>

#include <random>
using namespace std;
typedef long long          ll;
typedef unsigned long long ull;
#define endl '\n'
using pll   = pair<ll, ll>;
using pii   = pair<int, int>;
const int N = 2e6 + 10;
mt19937   rnd(114514);
// #define int ll
// vector<int>   d[100010];
int           a[N];
vector<int>   p[100010];
constexpr int MAX = 100000;

struct DivisorData {
    std::array<std::vector<int>, MAX + 1> d{};

    constexpr DivisorData()
    {
        for (int i = 2; i <= MAX; i++) {
            for (int j = i; j <= MAX; j += i) {
                d[j].push_back(i);
            }
        }
    }

    constexpr const vector<int>& operator[](int x)
    {
        return d[x];
    }
} d;

void UraykevoliQwQ()
{
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        p[a[i]].push_back(i);
    while (q--) {
        ll k, l, r;
        cin >> k >> l >> r;
        ll ans = 0;
        while (l <= r) {
            bool isok = 0;
            int  nxt  = r;
            for (auto x : d[k]) {
                auto it = lower_bound(p[x].begin(), p[x].end(), l);
                if (it != p[x].end() && *it <= r) {
                    isok = 1;
                    nxt  = min(nxt, *it);
                }
            }
            if (!isok) {
                ans += k * (r - l + 1);
                break;
            } else {
                ans += (nxt - l) * k;
                while (k % a[nxt] == 0)
                    k /= a[nxt];
                l = nxt;
            }
        }
        cout << ans << endl;
    }
    for (int i = 1; i <= n; i++)
        p[a[i]].clear();
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    // for (int i = 2; i <= 100000; i++) {
    //     for (int j = i; j <= 100000; j += i) {
    //         d[j].push_back(i);
    //     }
    // }
    int _ = 1;
    cin >> _;
    while (_--)
        UraykevoliQwQ();
    // return 0;
}