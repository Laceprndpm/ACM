#include <iostream>
#include <map>
#include <queue>
#include <vector>
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
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<i64> colorCnt(n + 1);
    for (int i = 1; i <= n; i++) {
        int co;
        cin >> co;
        colorCnt[co]++;
    }
    auto cmp = [&](int u, int v) {
        return colorCnt[u] < colorCnt[v];
    };
    priority_queue<i64, vector<i64>, decltype(cmp)> pq(cmp);
    for (int i = 1; i <= n; i++) {
        pq.push(i);
    }
    vector<vector<vector<i64>>> lev(n + 1);
    i64                         lv   = 0;
    int                         idx  = 0;
    int                         mxlv = 0;
    lev[0].push_back({});
    for (char cmd : s) {
        if (cmd == '(') {
            lev[lv].back().push_back(idx);
            idx++;
            lv++;
            lev[lv].push_back({});
            mxlv = max<i64>(lv, mxlv);
        } else {
            lv--;
        }
    }
    mxlv--;
    vector<i64> ans(n);
    for (int i = mxlv; i >= 0; i--) {
        auto& curLev = lev[i];
        for (auto block : curLev) {
            vector<i64> usedColor;
            for (int j : block) {
                ans[j] = pq.top();
                if (colorCnt[pq.top()] == 0) {
                    cout << "NO\n";
                    return 0;
                }
                usedColor.push_back(pq.top());
                pq.pop();
                colorCnt[ans[j]]--;
            }
            for (auto j : usedColor) {
                pq.push(j);
            }
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    return 0;
}