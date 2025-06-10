#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
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

    // 禁止隐式转换
    explicit operator double() const
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
    static bool less(const T& a, const T& b)
    {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }
};

template <class T, template <typename> class ComparePolicy = SimpleXY>
struct Point {
    T x, y;

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

    T operator^(const Point& t) const
    {
        return x * t.y - y * t.x;
    }

    bool operator<(const Point& t) const
    {
        return ComparePolicy<Point>::less(*this, t);
    }

    bool operator==(const Point& t) const
    {
        return x == t.x && y == t.y;
    }

    friend T edist(const Point& a, const Point& b)
    {
        return hypot(a.x - b.x, a.y - b.y);
    }

    friend T mdist(const Point& a, const Point& b)
    {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }

    void toChebyshev(void)
    {
        T tx = (x + y);
        T ty = (x - y);
        x = tx, y = ty;
    }

    void toManhattan(void)
    {
        T tx = (x + y) / 2;
        T ty = (x - y) / 2;
        x = tx, y = ty;
    }
};

class TreeArr {
private:
    vector<int> bitArr;

    int lowbit(int x)
    {
        return x & -x;
    }

public:
    TreeArr(int size) : bitArr(size) {}

    void update(int place, int value)
    {
        assert(place > 0);
        for (int i = place; i < (int)bitArr.size(); i += lowbit(i)) {
            bitArr[i] += value;
        }
    }

    int query(int place)
    {
        int res = 0;
        for (int i = place; i; i -= lowbit(i)) {
            res += bitArr[i];
        }
        return res;
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
    i64 b, n, d, m;
    cin >> b >> n >> d >> m;
    if (b == 2) {
        vector<Point<i64>> vec;
        for (int i = 0; i < n; i++) {
            i64 x, y;
            cin >> x >> y;
            Point p{x, y};
            p.toChebyshev();
            vec.push_back(p);
        }
        sort(vec.begin(), vec.end());
        int           i = 0, j = 0;
        constexpr int offset = 75010 * 2;
        TreeArr       tr(offset * 4);
        i64           ans = 0;
        for (; i < n; i++) {
            while (j < i && vec[i].x - vec[j].x > d) {
                tr.update(vec[j].y + offset, -1);
                ++j;
            }
            ans += tr.query(vec[i].y + d + offset) - tr.query(vec[i].y - d - 1 + offset);
            tr.update(vec[i].y + offset, 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
