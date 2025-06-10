#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct F {
    double v;

    static constexpr double eps = 1e-8;

    F(double _v = 0) : v(_v) {}

    // 隐式转换
    operator double() const
    {
        return v;
    }

    // 比较
    bool operator==(const F& o) const
    {
        return abs(v - o.v) < eps;
    }

    bool operator<(const F& o) const
    {
        return v + eps < o.v;
    }

    bool operator>(const F& o) const
    {
        return v - eps > o;
    }

    // 运算符重载
    F operator+(const F& o) const
    {
        return v + o.v;
    }

    F operator-(const F& o) const
    {
        return v - o.v;
    }

    F operator*(const F& o) const
    {
        return v * o.v;
    }

    F operator/(const F& o) const
    {
        return v / o.v;
    }

    F operator-() const
    {
        return -v;
    }
};

template <class T>
struct SimpleXY {
    constexpr static bool less(const T& a, const T& b)
    {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }

    constexpr static bool greater(const T& a, const T& b)
    {
        return a.x == b.x ? a.y > b.y : a.x > b.x;
    }
};

template <class T, template <typename> class ComparePolicy = SimpleXY>
struct Point {
    T x, y;

    Point(){};

    Point(T _x, T _y) : x(_x), y(_y) {}

    Point(pair<T, T> t) : x(t.first), y(t.second) {}

    Point(complex<T> c) : x(c.real()), y(c.imag()) {}

    Point operator+(const Point& t) const
    {
        return {x + t.x, y + t.y};
    }

    Point operator-(const Point& t) const
    {
        return {x - t.x, y - t.y};
    }

    void operator+=(const Point& t)
    {
        x += t.x, y += t.y;
    }

    void operator-=(const Point& t)
    {
        x -= t.x, y -= t.y;
    }

    Point operator*(T t) const
    {
        return {x * t, y * t};
    }

    friend Point operator*(T t, Point x)
    {
        return x * t;
    }

    Point operator/(T t) const
    {
        return {x / t, y / t};
    }

    T operator*(const Point& t) const
    {
        return x * t.x + y * t.y;
    }

    T operator%(const Point& t) const
    {
        return x * t.y - y * t.x;
    }

    Point operator=(const Point& t)
    {
        x = t.x, y = t.y;
        return *this;
    }

    bool operator<(const Point& t) const
    {
        return ComparePolicy<Point>::less(*this, t);
    }

    bool operator>(const Point& t) const
    {
        return ComparePolicy<Point>::greater(*this, t);
    }

    bool operator==(const Point& t) const
    {
        return x == t.x && y == t.y;
    }

    // 欧几里得距离
    T edist(const Point& b)
    {
        return hypot(x - b.x, y - b.y);
    }

    // 曼哈顿距离
    T mdist(const Point& b)
    {
        return abs(x - b.x) + abs(y - b.y);
    }

    // 转换到切比雪夫坐标系
    void toChebyshev(void)
    {
        T tx = (x + y);
        T ty = (x - y);
        x = tx, y = ty;
    }

    // 转换到曼哈顿坐标系
    void toManhattan(void)
    {
        T tx = (x + y) / 2;
        T ty = (x - y) / 2;
        x = tx, y = ty;
    }
};

struct Tubao {
    vector<int>  stk;
    vector<bool> used;
    vector<int>  doublemapping;
    int          tp;  // 初始化栈

    Tubao(int n, vector<Point<F>> p) : stk(n + 2), used(n + 1), doublemapping(n)
    {
        tp = 0;  // 初始化栈
        vector<int> mapping(n);
        iota(mapping.begin(), mapping.end(), 0);
        sort(mapping.begin(), mapping.end(), [&](int a, int b) {
            return p[a] < p[b];
        });
        // vector<int> doublemapping(n);
        for (int i = 0; i < n; i++) {
            doublemapping[mapping[i]] = i;
        }
        sort(p.begin(), p.end(), less<>());  // 对点进行排序
        stk[++tp] = 0;
        // 栈内添加第一个元素，且不更新 used，使得 1 在最后封闭凸包时也对单调栈更新
        for (int i = 1; i < n; ++i) {
            while (tp >= 2  // 下一行 * 操作符被重载为叉积
                   && ((p[stk[tp]] - p[stk[tp - 1]]) % (p[i] - p[stk[tp]])) <= F(0))
                used[stk[tp--]] = 0;
            used[i]   = 1;  // used 表示在凸壳上
            stk[++tp] = i;
        }
        int tmp = tp;  // tmp 表示下凸壳大小
        for (int i = n - 2; i >= 0; --i) {
            if (!used[i]) {
                // ↓求上凸壳时不影响下凸壳
                while (tp > tmp && ((p[stk[tp]] - p[stk[tp - 1]]) % (p[i] - p[stk[tp]])) <= F(0))
                    used[stk[tp--]] = 0;
                used[i]   = 1;
                stk[++tp] = i;
            }
        }
        vector<bool> tempused(n);
        for (int i = 0; i < n; i++) {
            tempused[i] = used[doublemapping[i]];
        }
        used = std::move(tempused);
        for (int i = 1; i <= tp; i++) {
            stk[i] = mapping[stk[i]];
        }
    }
};

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // stk[] 是整型，存的是下标
    // p[] 存储向量或点
    int n;
    cin >> n;
    vector<Point<F>> p(n);
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        p[i] = {x, y};
    }
    // sort(p.begin(), p.end());
    Tubao tb(n, p);
    auto  genCmp = [&](const Point<F>& o) -> auto {
        auto cmp = [&](int a, int b) -> bool {
            auto l1 = p[a] - o, l2 = p[b] - o;
            if (l1.y > F(0) && l2.y < F(0)) {
                return true;
            } else if (l1.y < F(0) && l2.y > F(0)) {
                return false;
            } else {
                return (l1 % l2) > F(0);
            }
        };
        return cmp;
    };
    vector<vector<int>> every(n);
    for (int i = 0; i < n; i++) {
        if (tb.used[i]) continue;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            every[i].emplace_back(j);
        }
        auto cmp = genCmp(p[i]);
        sort(every[i].begin(), every[i].end(), cmp);
    }
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        if (tb.used[i]) continue;
        every[i].emplace_back(every[i].front());
        for (int j = 0; j < n - 1; j++) {
            if (tb.used[every[i][j]] && tb.used[every[i][j + 1]]) {
                ans++;
            }
        }
    }
    cout << ans + 1 << '\n';
    return 0;
}
