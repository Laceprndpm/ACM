#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
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

// 万能打印运算符
template <class T>
std::ostream& dbg_print(std::ostream& os, const T& val)
{
    detail::smart_print(os, val);
    return os;
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

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    using st = multiset<int, greater<>>;
    map<pair<st, st>, bool> mp;
    // 首先，我可以随意弃牌，弃大选择多，弃小消耗小，难以证明弃小一定最优
    multiset<int, greater<>> a;
    multiset<int, greater<>> b;
    multiset<int, greater<>> c;
    int                      n, m, l;
    cin >> n >> m >> l;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        a.insert(cur);
    }
    for (int i = 0; i < m; i++) {
        int cur;
        cin >> cur;
        b.insert(cur);
    }
    for (int i = 0; i < l; i++) {
        int cur;
        cin >> cur;
        c.insert(cur);
    }
    function<bool(st a, st b, st c)> dfs = [&](st a, st b, st c) -> bool {
        if (a.empty()) return false;
        if (b.empty()) return true;
        if (mp.count({a, b})) return mp[{a, b}];
        bool win = 0;
        for (auto it = a.begin(); it != a.end(); it++) {
            if (next(it) != a.end() && c.upper_bound(*it) == c.upper_bound(*next(it))) continue;
            st aa(a.begin(), it), bb(b), cc(c);
            cc.insert(*it);
            auto afterit = it;
            afterit++;
            aa.insert(afterit, a.end());
            auto inerit = cc.upper_bound(*it);
            if (inerit != cc.end()) {
                aa.insert(*inerit);
                cc.erase(inerit);
            }
            // dbg(aa);
            // dbg(bb);
            // dbg(cc);
            win |= !dfs(bb, aa, cc);
        }
        return (mp[{a, b}] = win);
    };
    bool win = dfs(a, b, c);
    if (win) {
        cout << "Takahashi";
    } else {
        cout << "Aoki";
    }
    return 0;
}