#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
constexpr int N   = 200000 * 31;

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

// 万能打印运算符
template <class T, class... Args>
void dbg_print(std::ostream& os, const T& val, const Args... arg)
{
    if constexpr (sizeof...(arg) == 0) {
        (detail::smart_print(os, val));
        return;
    } else {
        detail::smart_print(os, val);
        os << ", ";
        detail::smart_print(os, arg...);
    }
}

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"
#ifdef NDEBUG
#define dbg(...) ((void)0)
#else
#define dbg(...) \
    std::cerr << RED << #__VA_ARGS__ << " = ", dbg_print(std::cerr, __VA_ARGS__), std::cerr << RESET << '\n'
#endif

int tot;

int trie[N][2];
i64 val[N];
int cnt[N];

int newNode()
{
    int x      = ++tot;
    trie[x][0] = trie[x][1] = 0;
    val[x]                  = 0;
    return x;
}

void init()
{
    tot = 0;
    newNode();
}

void add(int x)
{
    int t = x;
    int o = 1;
    for (int i = 0; i <= 29; i++) {
        int& p = trie[o][x >> i & 1];
        if (!p) {
            p = newNode();
        }
        o = p;
        val[o] += t;
        cnt[o]++;
    }
}

tuple<i64, i64> query(int x, int pos)
{
    int o = 1;
    for (int i = 0; i <= pos; i++) {
        int d = x >> i & 1;
        if (cnt[trie[o][d]]) {
            o = trie[o][d];
        } else {
            return {0, 0};
        }
    }
    return {val[o], cnt[o]};
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    init();
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) {
        cin >> i;
    }
    // 已知a，使得 f(a + b) == 1 << n
    // 那么a + b的后n位都是0，且第n+1位不是0
    // a + b = xxx1(00000)
    //
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        add(arr[i]);
        int cur = arr[i];
        for (int j = 29; j >= 0; j--) {
            int curJ = cur >> j & 1;
            cur &= ~(1 << j);       // 清空第j位，保证j及以上是0
            int consider = 1 << j;  // 考虑加起来后，1<<j是1，后面全是0
            consider -= cur;
            if (curJ) {
                consider ^= (1 << j);
            }
            // if (consider == 4 || j == 3) {
            //     // dbg(query(consider, j));
            //     // dbg(consider, j);
            // }
            auto&& [val, cnt] = query(consider, j);
            ans += (val + (cnt * arr[i])) >> j;
        }
    }
    cout << ans << '\n';
    return 0;
}