#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
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
#define dbg(...)
#endif
int times = 0;
int n;

int query(vector<int> vec, int k = -1)
{
    times++;
    if (times >= 550) exit(1);
    if (k == -1) {
        k = sz(vec);
    }
    cout << "? " << k << ' ';
    for (int i : vec) {
        assert(i <= n && i >= 1);
        cout << i << ' ';
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

int query(int l, int r)
{
    times++;
    if (times >= 550) exit(1);
    int k = r - l + 1;
    cout << "? " << k << ' ';
    for (int i = l; i <= r; i++) {
        assert(i <= n && i >= 1);
        cout << i << ' ';
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

void solve()
{
    times = 0;
    cin >> n;
    // 首先
    // 我可以花log(n)次，获得一个(,然后我直接暴力对每两个都来一次查询
    // ((**查询
    //
    // 如果是)(，则(()(答案为1
    // 如果是)),(())，答案为2
    // 如果是()，答案为1
    // 如果是((，答案为0
    //
    // ((**)查询：
    // ((:1
    // )):2
    // ():2
    // )(:3
    //
    // ()((**)
    // ((:1
    // )):1 + 3 = 4
    // )(:1 + 3 = 4
    // ():2
    //
    // ((**)()
    // ((:3
    // )):2
    // ():1 + 3 = 4
    // )(:3+2+1 = 6
    //
    // ((**(((**进行查询时，信息如何合并？
    // 只能说不劣，不能保证更优
    // 我可以知道前n个有多少)
    //
    // 如果无前缀，则仅()为1
    // (((***查询时
    // ()(
    // ))):3
    // ))(:2
    // )():3
    // )((:1
    // ()):2
    // ()(:1
    // (((:0
    //
    // 如果(**)查询
    // ():2
    // )):1
    // ((:1
    // )(:3
    //
    // 如果)**)查询
    // 等价与**)
    // 这样难以破坏对称性
    // ()
    // 如果对一个区间查询，返回了1，则说明有一个()，可以二分找到，然后剩下的一定是)))()((((或))))()))))这样的
    // 区间为0则没有查下去的必要，区间为2，则两个()分离或(())。
    // 区间为3,可能3个()分离，((()))或()()
    // 怎么描述这个子串为()的数量？
    //
    //
    // ((**)()
    // ((:3
    // )):2
    // ():1 + 3 = 4
    // )(:3+2+1 = 6
    // (**)()
    // ((:3
    //
    //
    // ((**))()
    // ():5
    // )):3
    // ((:4
    // )(:(()())() = 6
    //
    //
    int init_res = query(1, n);
    if (init_res == 0) {
        int l = 1, r = n;
        int ans = 0;
        while (l <= r) {
            int mid     = (l + r) / 2;
            int cur_res = query({n, mid});
            if (cur_res) {
                ans = mid;
                l   = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << "! " << string(ans, ')') + string(n - ans, '(') << endl;
    } else {
        int l = 1, r = n;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (query(l, mid)) {  // 如果从l,mid存在一个
                r = mid;
            } else {  // 去另一边
                if (mid + 1 <= n && query(mid, mid + 1)) {
                    l = mid, r = mid + 1;
                    break;
                } else {
                    l = mid + 1;
                }
            }
        }
        bool find = 0;
        for (int i = max(l - 2, 1); i <= min(l + 2, n - 1); i++) {
            if (query(i, i + 1)) {
                l = i, r = i + 1;
                find = 1;
                break;
            }
        }
        // ((()))
        assert(find);
        string ans;
        int    left_pos = l, right_pos = r;
        for (int i = 1; i + 1 <= n; i += 2) {
            int res = query({left_pos, left_pos, i, i + 1, right_pos, right_pos, left_pos, right_pos});
            if (res == 4) {
                ans += "((";
            } else if (res == 3) {
                ans += "))";
            } else if (res == 5) {
                ans += "()";
            } else if (res == 6) {
                ans += ")(";
            } else {
                assert(0);
            }
        }
        if (n % 2 == 1) {
            if (query({left_pos, n}))
                ans += ")";
            else
                ans += "(";
        }
        cout << "! " << ans << endl;
    }
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