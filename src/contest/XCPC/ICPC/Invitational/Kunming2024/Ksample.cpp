#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <regex>
#include <vector>

using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

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
#define mt      make_tuple
#define fi      first
#define se      second

// https://trap.jp/post/1224/
#define FOR1(a)                       for (i64 _ = 0; _ < i64(a); ++_)
#define FOR2(i, a)                    for (i64 i = 0; i < i64(a); ++i)
#define FOR3(i, a, b)                 for (i64 i = a; i < i64(b); ++i)
#define FOR4(i, a, b, c)              for (i64 i = a; i < i64(b); i += (c))
#define FOR1_R(a)                     for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR2_R(i, a)                  for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR3_R(i, a, b)               for (i64 i = (b) - 1; i >= i64(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...)    d
#define FOR(...)                      overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...)                    overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

constexpr int INF = 1e9;

namespace detail {

// 检测是否可迭代
template <class T, class = void>
struct is_iterable : std::false_type {};

template <class T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin())>> : std::true_type {};

// 递归打印
template <class T>
void smart_print(std::ostream& os, const T& val, int indent = 0)
{
    if constexpr (is_iterable<T>::value && !std::is_same_v<T, std::string>) {
        if (indent == 0) {
            os << '\n';
        }
        using element_type   = typename T::value_type;
        constexpr bool is_2d = is_iterable<element_type>::value;
        os << (is_2d ? "[\n" : "[");
        for (auto it = val.begin(); it != val.end();) {
            if constexpr (is_2d) os << std::string(indent + 2, ' ');
            smart_print(os, *it, indent + 2);
            if (++it != val.end()) os << (is_2d ? ",\n" : ", ");
        }
        os << (is_2d ? "\n" + std::string(indent, ' ') : "") << "]";
    } else {
        os << val;  // 基础类型直接输出
    }
}
}  // namespace detail

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

void flush() { std::cerr.flush(); }

template <class T>
void dbg_wt(const T& val)
{
    std::cerr << RED;
    detail::smart_print(std::cerr, val);
    std::cerr << RESET;
}

void print() { dbg_wt('\n'); }

template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail)
{
    dbg_wt(head);
    if (sizeof...(Tail)) dbg_wt(' ');
    print(forward<Tail>(tail)...);
}

#if defined(DEBUG)
#define dbg(...)                                    dbg_IMPL(__VA_ARGS__, dbg6, dbg5, dbg4, dbg3, dbg2, dbg1)(__VA_ARGS__)
#define dbg_IMPL(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define dbg1(x)                                     print(#x, "=", (x)), flush()
#define dbg2(x, y)                                  print(#x, "=", (x), #y, "=", (y)), flush()
#define dbg3(x, y, z)                               print(#x, "=", (x), #y, "=", (y), #z, "=", (z)), flush()
#define dbg4(x, y, z, w)                            print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w)), flush()
#define dbg5(x, y, z, w, v)                         print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v)), flush()
#define dbg6(x, y, z, w, v, u) \
    print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v), #u, "=", (u)), flush()
#else
#define dbg(...)
#endif
mt19937     rd(time(0));
vector<int> hidden;

int n;

void init()
{
    hidden = vector<int>(n + 1);
    iota(all(hidden), 0);
    shuffle(hidden.begin() + 1, hidden.end(), rd);
}

int guess(const vector<int>& gu)
{
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (gu[i] == hidden[i]) {
            cnt++;
        }
    }
    return cnt;
}

int askt = 0;

int aak(vector<int> ask)
{
    askt++;
    cout << 0;
    // for (int i = 1; i <= n; i++) {
    //     cout << ' ' << ask[i];
    // }
    cout << endl;
    int res = guess(ask);
    return res;
    cerr << RED << askt << RESET << endl;
}

void solve()
{
    cin >> n;
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }
    init();
    vector<int> change(n + 1);
    iota(all(change), 0);
    shuffle(change.begin() + 1, change.end(), rd);
    auto ask = [&](int l, int r, int a, int b) {
        vector<int> bb(n + 1);
        int         m = (l + r) / 2;
        for (int i = 1; i < m; i++) {
            bb[i] = change[a];
        }
        for (int i = m; i < n + 1; i++) {
            bb[i] = change[b];
        }
        int res = aak(bb);
        return res;
    };
    vector<int> ans(n + 1);
    int         mustrgt = -1;
    vector<int> gstp(20 + 2);
    vector<int> gstpbad(20 + 2);
    vector<int> gstpgood(20 + 2);

    auto dfs = [&](auto&& self, int l, int r, vector<int> cur, int dep) -> void {
        int cntgood = 0;
        int cntbad  = 0;
        int in      = askt;
        // assert(r - l == cur.size());
        if (r - l != cur.size()) {
            cout << "r - l != cur.size()\n";
            exit(0);
        }
        shuffle(all(cur), rd);
        if (r == l) {
            cout << "L != R\n";
            exit(0);
        }

        if (r - l == 1) {
            ans[l] = cur[0];
            return;
        }
        if (r - l == 2) {
            int res = ask(l, r, cur[0], mustrgt);
            if (res == 2) {
                ans[l]     = cur[0];
                ans[l + 1] = cur[1];
            } else if (res == 1) {
                ans[l + 1] = cur[0];
                ans[l]     = cur[1];
            } else {
                cout << "WA\n";
                exit(0);
            }
            return;
        }
        int         m = (l + r) / 2;
        vector<int> lft, rgt;
        int         i;
        for (i = 0; i + 1 < (r - l); i += 2) {
            if (lft.size() == (m - l)) {
                rgt.pb(cur[i]);
                rgt.pb(cur[i + 1]);
                continue;
            } else if (rgt.size() == r - m) {
                lft.pb(cur[i]);
                lft.pb(cur[i + 1]);
                continue;
            }
            int res = ask(l, r, cur[i], cur[i + 1]);
            if (res == 0) {
                lft.pb(cur[i + 1]);
                rgt.pb(cur[i]);
                cntgood++;
            } else if (res == 2) {
                lft.pb(cur[i]);
                rgt.pb(cur[i + 1]);
                cntgood++;
            } else {
                cntbad++;
                int res2 = ask(l, r, cur[i], mustrgt);
                if (res2 == 1) {
                    rgt.pb(cur[i]);
                    rgt.pb(cur[i + 1]);
                } else if (res2 == 2) {
                    lft.pb(cur[i]);
                    lft.pb(cur[i + 1]);
                } else {
                    cout << "WA\n";
                }
            }
        }
        if (i < r - l) {
            if (lft.size() != m - l) {
                lft.pb(cur[i]);
            } else if (rgt.size() != r - m) {
                rgt.pb(cur[i]);
            } else {
                cout << "WA\n";
            }
        }
        int out = askt;
        gstp[dep] += out - in;
        gstpgood[dep] += cntgood;
        gstpbad[dep] += cntbad;

        self(self, l, m, lft, dep + 1);
        self(self, m, r, rgt, dep + 1);
    };
    vector<int> vec;
    auto        spask = [&](int a, int b) {
        vector<int> bb(n + 1);
        for (int i = 1; i <= n - 1; i++) {
            bb[i] = change[a];
        }
        bb[n]   = change[b];
        int res = aak(bb);
        return res;
    };

    for (int i = 1; i + 1 <= n; i += 2) {
        int res = spask(i, i + 1);
        if (res == 2) {
            mustrgt = i + 1;
            break;
        } else if (res == 0) {
            mustrgt = i;
            break;
        }
    }
    if (mustrgt == -1) {
        mustrgt = n;
    }
    ans[n] = mustrgt;
    for (int i = 1; i <= n; i++) {
        if (i == mustrgt) continue;
        vec.pb(i);
    }
    dfs(dfs, 1, n, vec, 0);
    for (int i = 1; i <= n; i++) {
        ans[i] = change[ans[i]];
    }
    cout << 1 << ' ';
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    cerr << RED << askt << RESET << endl;
    dbg(gstp);
    dbg(gstpgood);
    dbg(gstpbad);
}

//
// 1  0 1 1 1 1 2
// 1  0 2 2 2 2 1
// 2  0 2 2 2 2 5
// 1  0 2 2 1 1 1
// 1  0 2 2 5 5 5
// 1  0 4 4 3 3 3
// 2  0 4 4 5 5 5
// 1  0 4 5 5 5 5
// 2  0 2 2 2 5 5
signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    t = 1;
    while (t--) {
        solve();
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
