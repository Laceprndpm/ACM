#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
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
#define dbg(...)
#endif

void solve()
{
    int n, k;
    cin >> n >> k;
    // 最大的问题，即不同长度间，性价比无法比较
    // abc
    // abcaa
    // 后者明显优于前者，而这又取决于其他字符串是否有aaa。。。
    // 哦，长度最多为10,感觉lcm() = 2520 + 某种dp，a + b 对比 c + d
    // 无穷背包？
    //
    // 贪心：
    // 先按照顺序排序，选择最短的哪个，检查，直到字典序>的位置
    // 此时，就获得了10个长度不同开头的，对于每个长度，都可以再来一次？把所有上面的字符串前缀加入后
    // 或者也许精确地说，我们只需要每个长度中最小的？
    //
    vector<string> s_vec(n);
    for (int i = 0; i < n; i++) {
        cin >> s_vec[i];
    }
    sort(all(s_vec));
    array<string, 11> candi({});
    for (int i = 0; i < n; i++) {
        if (candi[len(s_vec[i])].empty()) {
            candi[len(s_vec[i])] = ' ' + s_vec[i];
        }
    }
    for (int i = 1; i <= 10; i++) {
        if (candi[i].empty()) {
            continue;
        }
        for (int j = 1; j <= 10; j++) {
            if (i == j) continue;
            if (candi[j].empty()) continue;
            for (int kk = 1; kk <= min(i, j); kk++) {
                if (candi[i][kk] < candi[j][kk]) {  // 必须删掉劣的字符串哦。。。否则后面添加到pq时会错误初始化取不到的
                    candi[j] = "";
                    break;
                } else if (candi[i][kk] > candi[j][kk]) {  // 如果这里已经大于了，那么也许无法简单判断两个字符串吧？
                    break;
                }
            }
        }
    }

    struct item {
        i64    cur_len;
        string s;
        int    used = 0;

        int operator<(item& o)
        {
            if (cur_len == o.cur_len) return used < o.used;
            return (cur_len > o.cur_len);  // 长的沉入
        }
    };

    vector<char>                               min_c(2e6, INT8_MAX);
    priority_queue<item, vector<item>, less<>> pq;
    for (int i = 1; i <= 10; i++) {
        if (candi[i].empty()) continue;
        for (int j = 1; j <= i; j++) {
            min_c[j] = min(min_c[j], candi[i][j]);
        }
        string new_string = string(10 - i, ' ') + candi[i];
        assert(new_string.size() == 11);

        pq.push({i, new_string, 1});
    }
    int ans;

    vector<int> vis(2e6, 0);  // 必须，否则复杂度可能错误
    while (true) {
        item cur = pq.top();
        pq.pop();
        const string& s       = cur.s;  // len == 11，可以访问[1, 10]
        int           cur_len = cur.cur_len;
        bool          flag    = 1;
        for (int i = 0; i < 10; i++) {  // 倒序10个，因为每次最多更新10个吧
            if (cur_len - i <= 0) break;
            if (s[10 - i] > min_c[cur_len - i]) {
                flag = 0;
            }
        }
        if (!flag) continue;
        if (vis[cur_len]) continue;
        vis[cur_len] = 1;
        if (cur.used == k) {
            ans = cur.cur_len;
            break;
        }
        for (int i = 1; i <= 10; i++) {
            if (candi[i].empty()) continue;
            int update = 1;  // 默认更新
            for (int j = 1; j <= i; j++) {
                if (min_c[cur_len + j] > candi[i][j]) {  // 强更新
                    min_c[cur_len + j] = candi[i][j];
                    update             = 2;
                    break;
                } else if (min_c[cur_len + j] < candi[i][j]) {  // 无更新
                    update = 0;
                    break;
                }
            }
            if (update == 2) {  // 强更新
                int j;
                for (j = 1; j <= i; j++) {
                    min_c[cur_len + j] = candi[i][j];
                }
                for (; j <= 10; j++) {
                    min_c[cur_len + j] = 'z' + 1;
                }
            }
            if (update) {  // 同时放堆里面去
                string new_string =
                    string(s.begin() + i, s.begin() + 11) + string(candi[i].begin() + 1, candi[i].end());
                assert(new_string.size() == 11);
                pq.push({cur_len + i, new_string, cur.used + 1});
            }
        }
    }
    for (int i = 1; i <= ans; i++) {
        cout << min_c[i];
    }
    cout << '\n';
}

signed main(signed argc, char** argv)
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