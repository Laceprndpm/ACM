#include <bits/stdc++.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <stack>
#include <utility>
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
#define len(x)  int(x.size())
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

void flush()
{
    std::cerr.flush();
}

template <class T>
void dbg_wt(const T& val)
{
    std::cerr << RED;
    detail::smart_print(std::cerr, val);
    std::cerr << RESET;
}

void print()
{
    dbg_wt('\n');
}

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
#define dbg(...) void()
#endif

struct SuffixArray {
    int              n;
    std::vector<int> sa, rk, lc;

    SuffixArray(const std::string& s)
    {
        n = s.length();
        sa.resize(n);
        lc.resize(n - 1);
        rk.resize(n);
        std::iota(sa.begin(), sa.end(), 0);
        std::sort(sa.begin(), sa.end(), [&](int a, int b) {
            return s[a] < s[b];
        });
        rk[sa[0]] = 0;
        for (int i = 1; i < n; ++i)
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        int              k = 1;
        std::vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while (rk[sa[n - 1]] < n - 1) {
            tmp.clear();
            for (int i = 0; i < k; ++i)
                tmp.push_back(n - k + i);
            for (auto i : sa)
                if (i >= k) tmp.push_back(i - k);
            std::fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; ++i)
                ++cnt[rk[i]];
            for (int i = 1; i < n; ++i)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i)
                sa[--cnt[rk[tmp[i]]]] = tmp[i];
            std::swap(rk, tmp);
            rk[sa[0]] = 0;
            for (int i = 1; i < n; ++i)
                rk[sa[i]] =
                    rk[sa[i - 1]]
                    + (tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == n || tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
            k *= 2;
        }
        for (int i = 0, j = 0; i < n; ++i) {
            if (rk[i] == 0) {
                j = 0;
            } else {
                for (j -= j > 0; i + j < n && sa[rk[i] - 1] + j < n && s[i + j] == s[sa[rk[i] - 1] + j];)
                    ++j;
                lc[rk[i] - 1] = j;
            }
        }
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<string> sarr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> sarr[i];
    }
    string s = "";
    // expected:**belong**
    vector<int> seg_begin(n + 3);
    for (int i = 1; i <= n; i++) {
        seg_begin[i] = len(s);
        s            = s + sarr[i] + "#";
    }
    seg_begin[n + 1] = len(s);  // 每个有效段的开头
    SuffixArray suffix_array(s);
    SuffixArray test("aabc");
    dbg(test.sa);
    dbg(test.lc);
    const i64 len_s = len(s) - 1;

    // **suffix_place**
    vector<int> belong(len_s + 1);

    int cnt_end_char = 1;

    for (int i = 0; i <= len_s; i++) {
        belong[i] = cnt_end_char;
        if (s[i] == '#') cnt_end_char++;
    }
    const auto&                      sa = suffix_array.sa;
    const auto&                      rk = suffix_array.rk;
    const auto&                      lc = suffix_array.lc;
    stack<pair<i64, array<i64, 51>>> mono_stk;
    i64                              ans = 0;

    auto add_inplace = [](array<i64, 51>& a, const array<i64, 51>& b) -> void {
        for (int i = 1; i <= 50; i++) {
            a[i] = max(a[i], b[i]);
        }
    };

    auto calc = [](array<i64, 51> arr) -> i64 {
        i64 cur_val = 0;
        int cnt     = 0;
        for (int i = 1; i <= 50; i++) {
            if (arr[i] == 0) continue;
            cnt++;
            cur_val += arr[i];
        }

        if (cnt < 2) {
            return 0ll;
        } else {
            return cur_val;
        }
    };

    for (int i = 1; i <= len_s; i++) {
        assert(sa.size() > i);
        i64 p1 = sa[i - 1], p2 = sa[i];  // suffix_place
        if (s[p1] == '#' || s[p2] == '#') continue;
        i64 cur_len            = lc[i - 1];
        cur_len                = min(cur_len, seg_begin[belong[p1] + 1] - p1 - 1);
        cur_len                = min(cur_len, seg_begin[belong[p2] + 1] - p2 - 1);  // 下一段开头-当前
        array<i64, 51> cur_arr = {0};

        while (!mono_stk.empty() && mono_stk.top().fi >= cur_len) {
            auto [stk_cur_len, top_arr] = mono_stk.top();
            mono_stk.pop();
            add_inplace(cur_arr, top_arr);
            ans = max(ans, stk_cur_len * calc(cur_arr));
        }

        cur_arr[belong[p1]] = max(cur_arr[belong[p1]], p1 - seg_begin[belong[p1]] + 1);
        cur_arr[belong[p2]] = max(cur_arr[belong[p2]], p2 - seg_begin[belong[p2]] + 1);
        mono_stk.push({cur_len, cur_arr});
        ans = max(ans, cur_len * calc(cur_arr));
    }

    if (mono_stk.size() > 1) {
        auto [cur_len, b] = mono_stk.top();
        ans               = max(ans, cur_len * calc(b));
        mono_stk.pop();
        while (mono_stk.size()) {
            auto [nxt_len, a] = mono_stk.top();
            mono_stk.pop();
            add_inplace(b, a);
            ans = max(ans, nxt_len * calc(b));
        }
    }

    if (mono_stk.size()) {
        mono_stk.pop();
    }

    for (int i = len_s; i >= 1; i--) {
        i64 p1 = sa[i - 1], p2 = sa[i];  // suffix_place
        if (s[p1] == '#' || s[p2] == '#') continue;

        i64 cur_len            = lc[i - 1];
        cur_len                = min(cur_len, seg_begin[belong[p1] + 1] - p1 - 1);
        cur_len                = min(cur_len, seg_begin[belong[p2] + 1] - p2 - 1);
        array<i64, 51> cur_arr = {0};

        while (!mono_stk.empty() && mono_stk.top().fi >= cur_len) {
            auto [stk_cur_len, top_arr] = mono_stk.top();
            mono_stk.pop();
            add_inplace(cur_arr, top_arr);
            ans = max(ans, stk_cur_len * calc(cur_arr));
        }
        cur_arr[belong[p1]] = max(cur_arr[belong[p1]], p1 - seg_begin[belong[p1]] + 1);
        cur_arr[belong[p2]] = max(cur_arr[belong[p2]], p2 - seg_begin[belong[p2]] + 1);

        mono_stk.push({cur_len, cur_arr});
        ans = max(ans, cur_len * calc(cur_arr));
    }

    if (mono_stk.size() > 1) {
        auto [cur_len, b] = mono_stk.top();
        ans               = max(ans, cur_len * calc(b));
        mono_stk.pop();
        while (mono_stk.size()) {
            auto [nxt_len, a] = mono_stk.top();
            mono_stk.pop();
            add_inplace(b, a);
            ans = max(ans, nxt_len * calc(b));
        }
    }

    if (mono_stk.size()) {
        mono_stk.pop();
    }

    cout << ans << '\n';
}

signed main(signed argc, char** argv)
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

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */