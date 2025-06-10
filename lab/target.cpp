#include <iostream>
#include <map>
#include <vector>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << '[';
    for (const auto& x : vec)
        os << x << ", ";
    if (!vec.empty()) os << "\b\b";
    os << ']';
    return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& vec)
{
    os << "[\n";
    for (const auto& x : vec) {
        os << '[';
        for (const auto& y : x) {
            os << y << ", ";
        }
        if (!vec.empty()) os << "\b\b";
        os << ']';
        os << '\n';
    }
    os << ']';
    return os;
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m)
{
    os << '{';
    for (const auto& [k, v] : m)
        os << k << ": " << v << ", ";
    if (!m.empty()) os << "\b\b";
    os << '}';
    return os;
}

// 调试打印函数
template <typename... Args>
void dbg_print(std::ostream& os, Args&&... args)
{
    const char* sep = "";
    ((os << sep << std::forward<Args>(args), sep = ", "), ...);
}

#ifdef NDEBUG
#define dbg(...) ((void)0)
#else
#define dbg(...) \
    std::cerr << RED << #__VA_ARGS__ << " = ", dbg_print(std::cerr, __VA_ARGS__), std::cerr << RESET << '\n'
#endif

// 测试
int main()
{
    int                        x = 42;
    std::vector<int>           v = {1, 2, 3};
    std::map<std::string, int> m = {{"a", 1}, {"b", 2}};

    dbg(x, v);  // 绿色输出到 cout
    dbg(m);
    std::vector<std::vector<int>> bd = {{1, 2}, {2, 3}};
    dbg(bd);
    return 0;
}