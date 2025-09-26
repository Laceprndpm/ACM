#include <bitset>
#include <cassert>
#include <iostream>
#include <vector>
#ifndef CLANGD_MODE
#ifndef DEBUG
#define NDEBUG
#undef assert
#define assert(x) [[assume(x)]]
#include <bits/stdc++.h>
#endif
#endif
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
#define sz(x)   (i64)(std::size(x))
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
void smart_print(std::ostream &os, const T &val, int indent = 0)
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
void dbg_wt(const T &val)
{
    std::cerr << RED;
    detail::smart_print(std::cerr, val);
    std::cerr << RESET;
}

void print() { dbg_wt('\n'); }

template <class Head, class... Tail>
void print(Head &&head, Tail &&...tail)
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
constexpr int N = 2e5 + 2;

int popcnt(int x) { return __builtin_popcount(x); }

int popcnt(u32 x) { return __builtin_popcount(x); }

int popcnt(ll x) { return __builtin_popcountll(x); }

int popcnt(u64 x) { return __builtin_popcountll(x); }

template <class T>
using vc = vector<T>;

template <class T, class S>
inline bool chmin(T &a, const S &b)
{
    return (a > b ? a = b, 1 : 0);
}

template <class T, class S>
inline bool chmax(T &a, const S &b)
{
    return (a < b ? a = b, 1 : 0);
}

// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }

int topbit(u32 x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }

int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }

int topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }

// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
int lowbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); }

int lowbit(u32 x) { return (x == 0 ? -1 : __builtin_ctz(x)); }

int lowbit(ll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }

int lowbit(u64 x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }

// https://codeforces.com/contest/914/problem/F
// https://yukicoder.me/problems/no/142
// わずかに普通の bitset より遅いときもあるようだが，
// 固定長にしたくないときや slice 操作が必要なときに使う
struct My_Bitset {
    using T = My_Bitset;
    int     N;
    vc<u64> dat;

    // x で埋める
    My_Bitset(int N = 0, int x = 0) : N(N)
    {
        assert(x == 0 || x == 1);
        u64 v = (x == 0 ? 0 : -1);
        dat.assign((N + 63) >> 6, v);
        if (N) dat.back() >>= (64 * sz(dat) - N);
    }

    int size() { return N; }

    void resize(int size)
    {
        dat.resize((size + 63) >> 6);
        int remainingBits = size & 63;
        if (remainingBits != 0) {
            u64 mask = (u64(1) << remainingBits) - 1;
            dat.back() &= mask;
        }
        N = size;
    }

    void append(int idx, bool b)
    {
        assert(N == idx);
        resize(idx + 1), (*this)[idx] = b;
    }

    static T from_string(string &S)
    {
        int N = sz(S);
        T   ANS(N);
        FOR(i, N) ANS[i] = (S[i] == '1');
        return ANS;
    }

    // thanks to chatgpt!
    class Proxy {
    public:
        Proxy(vc<u64> &d, int i) : dat(d), index(i) {}

        operator bool() const { return (dat[index >> 6] >> (index & 63)) & 1; }

        Proxy &operator=(u64 value)
        {
            dat[index >> 6] &= ~(u64(1) << (index & 63));
            dat[index >> 6] |= (value & 1) << (index & 63);
            return *this;
        }

        void flip()
        {
            dat[index >> 6] ^= (u64(1) << (index & 63));  // XOR to flip the bit
        }

    private:
        vc<u64> &dat;
        int      index;
    };

    Proxy operator[](int i) { return Proxy(dat, i); }

    bool operator[](int i) const { return (dat[i >> 6] >> (i & 63)) & 1; }

    bool operator==(const T &p)
    {
        assert(N == p.N);
        FOR(i, sz(dat)) if (dat[i] != p.dat[i]) return false;
        return true;
    }

    T &operator&=(const T &p)
    {
        assert(N == p.N);
        FOR(i, sz(dat)) dat[i] &= p.dat[i];
        return *this;
    }

    T &operator|=(const T &p)
    {
        assert(N == p.N);
        FOR(i, sz(dat)) dat[i] |= p.dat[i];
        return *this;
    }

    T &operator^=(const T &p)
    {
        assert(N == p.N);
        FOR(i, sz(dat)) dat[i] ^= p.dat[i];
        return *this;
    }

    T operator&(const T &p) const { return T(*this) &= p; }

    T operator|(const T &p) const { return T(*this) |= p; }

    T operator^(const T &p) const { return T(*this) ^= p; }

    T operator~() const
    {
        T p = (*this);
        p.flip_range(0, N);
        return p;
    }

    void set_minus_inplace(T &other)
    {
        assert(N == other.N);
        FOR(i, sz(dat)) dat[i] = dat[i] & (~other.dat[i]);
    }

    T set_minus(T other)
    {
        assert(N == other.N);
        FOR(i, sz(dat)) other.dat[i] = dat[i] & (~other.dat[i]);
        return other;
    }

    int count()
    {
        int ans = 0;
        for (u64 val : dat) ans += popcnt(val);
        return ans;
    }

    int dot(T &p)
    {
        assert(N == p.N);
        int ans = 0;
        FOR(i, sz(dat)) ans += popcnt(dat[i] & p.dat[i]);
        return ans;
    }

    int next(int i)
    {
        chmax(i, 0);
        if (i >= N) return N;
        int k = i >> 6;
        {
            u64 x = dat[k];
            int s = i & 63;
            x     = (x >> s) << s;
            if (x) return (k << 6) | lowbit(x);
        }
        FOR(idx, k + 1, sz(dat))
        {
            if (dat[idx] == 0) continue;
            return (idx << 6) | lowbit(dat[idx]);
        }
        return N;
    }

    int prev(int i)
    {
        chmin(i, N - 1);
        if (i <= -1) return -1;
        int k = i >> 6;
        if ((i & 63) < 63) {
            u64 x = dat[k];
            x &= (u64(1) << ((i & 63) + 1)) - 1;
            if (x) return (k << 6) | topbit(x);
            --k;
        }
        FOR_R(idx, k + 1)
        {
            if (dat[idx] == 0) continue;
            return (idx << 6) | topbit(dat[idx]);
        }
        return -1;
    }

    My_Bitset range(int L, int R)
    {
        assert(L <= R);
        My_Bitset p(R - L);
        int       rm = (R - L) & 63;
        FOR(rm)
        {
            p[R - L - 1] = bool((*this)[R - 1]);
            --R;
        }
        int n  = (R - L) >> 6;
        int hi = L & 63;
        int lo = 64 - hi;
        int s  = L >> 6;
        if (hi == 0) {
            FOR(i, n) { p.dat[i] ^= dat[s + i]; }
        } else {
            FOR(i, n) { p.dat[i] ^= (dat[s + i] >> hi) ^ (dat[s + i + 1] << lo); }
        }
        return p;
    }

    My_Bitset slice(int L, int R) { return range(L, R); }

    int count_range(int L, int R)
    {
        assert(L <= R);
        int cnt = 0;
        while ((L < R) && (L & 63)) cnt += (*this)[L++];
        while ((L < R) && (R & 63)) cnt += (*this)[--R];
        int l = L >> 6, r = R >> 6;
        FOR(i, l, r) cnt += popcnt(dat[i]);
        return cnt;
    }

    // [L,R) に p を代入
    void assign_to_range(int L, int R, My_Bitset &p)
    {
        assert(p.N == R - L);
        int a = 0, b = p.N;
        while (L < R && (L & 63)) {
            (*this)[L++] = bool(p[a++]);
        }
        while (L < R && (R & 63)) {
            (*this)[--R] = bool(p[--b]);
        }
        // p[a:b] を [L:R] に
        int l = L >> 6, r = R >> 6;
        int s = a >> 6, t = b >> t;
        int n = r - l;
        if (!(a & 63)) {
            FOR(i, n) dat[l + i] = p.dat[s + i];
        } else {
            int hi               = a & 63;
            int lo               = 64 - hi;
            FOR(i, n) dat[l + i] = (p.dat[s + i] >> hi) | (p.dat[1 + s + i] << lo);
        }
    }

    // [L,R) に p を xor
    void xor_to_range(int L, int R, My_Bitset &p)
    {
        assert(p.N == R - L);
        int a = 0, b = p.N;
        while (L < R && (L & 63)) {
            dat[L >> 6] ^= u64(p[a]) << (L & 63);
            ++a, ++L;
        }
        while (L < R && (R & 63)) {
            --b, --R;
            dat[R >> 6] ^= u64(p[b]) << (R & 63);
        }
        // p[a:b] を [L:R] に
        int l = L >> 6, r = R >> 6;
        int s = a >> 6, t = b >> t;
        int n = r - l;
        if (!(a & 63)) {
            FOR(i, n) dat[l + i] ^= p.dat[s + i];
        } else {
            int hi = a & 63;
            int lo = 64 - hi;
            FOR(i, n) dat[l + i] ^= (p.dat[s + i] >> hi) | (p.dat[1 + s + i] << lo);
        }
    }

    // 行列基本変形で使うやつ
    // p は [i:N) にしかないとして p を xor する
    void xor_suffix(int i, My_Bitset &p)
    {
        assert(N == p.N && 0 <= i && i < N);
        FOR(k, i / 64, sz(dat)) { dat[k] ^= p.dat[k]; }
    }

    // [L,R) に p を and
    void and_to_range(int L, int R, My_Bitset &p)
    {
        assert(p.N == R - L);
        int a = 0, b = p.N;
        while (L < R && (L & 63)) {
            if (!p[a]) (*this)[L] = 0;
            a++, L++;
        }
        while (L < R && (R & 63)) {
            --b, --R;
            if (!p[b]) (*this)[R] = 0;
        }
        // p[a:b] を [L:R] に
        int l = L >> 6, r = R >> 6;
        int s = a >> 6, t = b >> t;
        int n = r - l;
        if (!(a & 63)) {
            FOR(i, n) dat[l + i] &= p.dat[s + i];
        } else {
            int hi = a & 63;
            int lo = 64 - hi;
            FOR(i, n) dat[l + i] &= (p.dat[s + i] >> hi) | (p.dat[1 + s + i] << lo);
        }
    }

    // [L,R) に p を or
    void or_to_range(int L, int R, My_Bitset const &p)
    {
        assert(p.N == R - L);
        int a = 0, b = p.N;
        while (L < R && (L & 63)) {
            dat[L >> 6] |= u64(p[a]) << (L & 63);
            ++a, ++L;
        }
        while (L < R && (R & 63)) {
            --b, --R;
            dat[R >> 6] |= u64(p[b]) << (R & 63);
        }
        // p[a:b] を [L:R] に
        int l = L >> 6, r = R >> 6;
        int s = a >> 6, t = b >> t;
        int n = r - l;
        if (!(a & 63)) {
            FOR(i, n) dat[l + i] |= p.dat[s + i];
        } else {
            int hi = a & 63;
            int lo = 64 - hi;
            FOR(i, n) dat[l + i] |= (p.dat[s + i] >> hi) | (p.dat[1 + s + i] << lo);
        }
    }

    // 行列基本変形で使うやつ
    // p は [i:N) にしかないとして p を or する
    void or_suffix(int i, My_Bitset &p)
    {
        assert(N == p.N && 0 <= i && i < N);
        FOR(k, i / 64, sz(dat)) { dat[k] |= p.dat[k]; }
    }

    // [L,R) を 1 に変更
    void set_range(int L, int R)
    {
        while (L < R && (L & 63)) {
            set(L++);
        }
        while (L < R && (R & 63)) {
            set(--R);
        }
        FOR(i, L >> 6, R >> 6) dat[i] = u64(-1);
    }

    // [L,R) を 1 に変更
    void reset_range(int L, int R)
    {
        while (L < R && (L & 63)) {
            reset(L++);
        }
        while (L < R && (R & 63)) {
            reset(--R);
        }
        FOR(i, L >> 6, R >> 6) dat[i] = u64(0);
    }

    // [L,R) を flip
    void flip_range(int L, int R)
    {
        while (L < R && (L & 63)) {
            flip(L++);
        }
        while (L < R && (R & 63)) {
            flip(--R);
        }
        FOR(i, L >> 6, R >> 6) dat[i] ^= u64(-1);
    }

    // bitset に仕様を合わせる
    void set(int i) { (*this)[i] = 1; }

    void reset(int i) { (*this)[i] = 0; }

    void flip(int i) { (*this)[i].flip(); }

    void set()
    {
        fill(all(dat), u64(-1));
        resize(N);
    }

    void reset() { fill(all(dat), 0); }

    void flip()
    {
        FOR(i, sz(dat) - 1) { dat[i] = u64(-1) ^ dat[i]; }
        int i = sz(dat) - 1;
        FOR(k, 64)
        {
            if (64 * i + k >= size()) break;
            flip(64 * i + k);
        }
    }

    bool any()
    {
        FOR(i, sz(dat))
        {
            if (dat[i]) return true;
        }
        return false;
    }

    bool ALL()
    {
        dat.resize((N + 63) >> 6);
        int r = N & 63;
        if (r != 0) {
            u64 mask = (u64(1) << r) - 1;
            if (dat.back() != mask) return 0;
        }
        for (int i = 0; i < N / 64; ++i)
            if (dat[i] != u64(-1)) return false;
        return true;
    }

    // bs[i]==true であるような i 全体
    vc<int> collect_idx()
    {
        vc<int> I;
        FOR(i, N) if ((*this)[i]) I.eb(i);
        return I;
    }

    bool is_subset(T &other)
    {
        assert((other.size()) == N);
        FOR(i, sz(dat))
        {
            u64 a = dat[i], b = other.dat[i];
            if ((a & b) != a) return false;
        }
        return true;
    }

    int _Find_first() { return next(0); }

    int _Find_next(int p) { return next(p + 1); }

    template <typename F>
    void enumerate(int L, int R, F f)
    {
        if (L >= size()) return;
        int p = ((*this)[L] ? L : _Find_next(L));
        while (p < R) {
            f(p);
            p = _Find_next(p);
        }
    }

    static string TO_STR[256];

    string to_string() const
    {
        if (TO_STR[0].empty()) precompute();
        string S;
        for (auto &x : dat) {
            FOR(i, 8) S += TO_STR[(x >> (8 * i) & 255)];
        }
        S.resize(N);
        return S;
    }

    static void precompute()
    {
        FOR(s, 256)
        {
            string x;
            FOR(i, 8) x += '0' + (s >> i & 1);
            TO_STR[s] = x;
        }
    }
};

string My_Bitset::TO_STR[256];  // END: ds/my_bitset.hpp

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>         fa(n + 1);
    vector<vector<int>> sons(n + 1);
    for (int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        sons[fa].pb(i);
    }
    vector<vector<int>> level(n + 1);
    int                 shallow = INF;
    auto                dfs     = [&](this auto &&dfs, int u, int depth) -> void {
        level[depth].pb(u);
        for (int v : sons[u]) {
            dfs(v, depth + 1);
        }
        if (sons[u].empty()) {
            shallow = min(shallow, depth);
        }
    };
    dfs(1, 1);
    vector<int> level_size(n + 1);
    for (int i = 1; i <= n; i++) {
        level_size[i] = level[i].size();
    }
    vector<int> prefix(n + 1);
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + level_size[i];
    }
    bitset<N> dp;  // 到第i层，花了j个白是否可行
    bitset<N> mask;
    for (int i = 0; i <= k; i++) {
        mask[i] = 1;
    }
    dp[0]  = 1;
    int mx = shallow - 1;
    for (int i = 0; i < shallow; i++) {
        int atleastwhite = max(0, prefix[i] - (n - k));
        int nextatleast  = max(0, prefix[i + 1] - (n - k));
        // dp[1][j + level_size[i + 1]] = 1;
        dp |= (dp << level_size[i + 1]);
        dp &= mask;
        for (int i = atleastwhite; i < nextatleast; i++) {
            dp[i] = 0;
        }
        if (i == shallow - 1 && dp.any()) mx = i + 1;
    }
    cout << mx << '\n';
}

signed main(signed argc, char **argv)
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

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */