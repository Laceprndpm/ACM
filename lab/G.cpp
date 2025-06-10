#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

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

    bool operator<(const Point& t)
    {
        return ComparePolicy<Point>::less(*this, t);
    }

    friend double edist(const Point& a, const Point& b)
    {
        return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
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
    int       n, m;
    const int offset = m + 1;
    TreeArr   tr;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Point p{i, j};
            p.toChebyshev();
        }
    }
    return 0;
}