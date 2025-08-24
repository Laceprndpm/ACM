#include <bitset>
#include <cassert>
#include <iostream>
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

void flush()
{
    std::cerr.flush();
}

template <class T>
void dbg_wt(const T &val)
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
template <class T, int R, int C>
struct OMatrix {
    T data[R][C]{};

    constexpr OMatrix() {}

    constexpr OMatrix(std::initializer_list<std::initializer_list<T>> init)
    {
        int i = 0;
        for (auto &row : init) {
            int j = 0;
            for (auto &val : row) {
                data[i][j++] = val;
            }
            ++i;
        }
    }

    constexpr OMatrix operator*=(const OMatrix &o) &
    {
        *this = *this * o;
        return *this;
    }

    constexpr OMatrix operator+=(const OMatrix &o) &
    {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                this->data[i][j] ^= o.data[i][j];
            }
        }
        return *this;
    }
};

template <class T, int R, int K, int C>
constexpr OMatrix<T, R, C> operator*(const OMatrix<T, R, K> &lhs, const OMatrix<T, K, C> &rhs)
{
    OMatrix<T, R, C> res;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            T sum{};
            for (int k = 0; k < K; k++) {
                sum += lhs.data[i][k] * rhs.data[k][j];
            }
            res.data[i][j] = sum % 2;
        }
    }
    return {res};
}

using M22               = OMatrix<short, 2, 2>;
M22                  RY = {{0, 1}, {1, 0}};
M22                  RB = {{1, 0}, {1, 1}};
M22                  YB = {{1, 1}, {0, 1}};
vector<bitset<2001>> b;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<M22> col(1000);
    for (auto &i : col) {
        i = M22{{1, 0}, {0, 1}};
    }
    FOR(i, k)
    {
        string s;
        cin >> s;
        if (s == "mix") {
            b.eb();
            b.eb();
        }
        int m;
        cin >> m;
        FOR(j, m)
        {
            int x;
            cin >> x;
            x--;
            if (s == "RY") {
                col[x] = RY * col[x];
            } else if (s == "RB") {
                col[x] = RB * col[x];
            } else if (s == "YB") {
                col[x] = YB * col[x];
            } else {
                assert(s == "mix");
                for (int i = 0; i < 2; i++) {
                    assert(col[x].data[i][0] < 2);
                    assert(col[x].data[i][1] < 2);
                }
                if (col[x].data[0][0]) b[sz(b) - 2][x * 2] = 1;
                if (col[x].data[1][0]) b[sz(b) - 1][x * 2] = 1;
                if (col[x].data[0][1]) b[sz(b) - 2][x * 2 + 1] = 1;
                if (col[x].data[1][1]) b[sz(b) - 1][x * 2 + 1] = 1;
            }
        }
        if (s == "mix") {
            char res;
            cin >> res;
            if (res == 'R' || res == 'B') b[sz(b) - 2][2000] = 1;
            if (res == 'Y' || res == 'B') b[sz(b) - 1][2000] = 1;
        }
    }
    int cur = 0;
    FOR(z, 2001)
    {
        FOR(i, cur, sz(b)) if (b[i][z] == 1)
        {
            swap(b[i], b[cur]);
            assert(b[cur][z] == 1);
            FOR(j, sz(b)) if (j != cur && b[j][z]) b[j] ^= b[cur];
            cur++;
            break;
        }
    }
    vector<int> tmp(n);
    FOR(i, sz(b))
    {
        int ind = 0;
        while (ind < 2001 && !b[i][ind]) ind++;
        if (ind == 2001) continue;
        if (ind == 2000) {
            puts("NO");
            exit(0);
        }
        assert(ind < 2 * n);
        if (ind % 2 == 0)
            tmp[ind / 2] += 2 * b[i][2000];
        else
            tmp[ind / 2] += b[i][2000];
    }
    puts("YES");
    FOR(i, n)
    {
        if (tmp[i] == 3)
            putchar('B');
        else if (tmp[i] == 2)
            putchar('R');
        else if (tmp[i] == 1)
            putchar('Y');
        else
            putchar('.');
    }
    puts("");
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
    int t = 1;
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