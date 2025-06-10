#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

template <class T>
class Fenwick {
private:
    vector<int> bitArr;

    int lowbit(int x)
    {
        return x & -x;
    }

public:
    Fenwick(int n) : bitArr(1 + n) {}

    void add(int place, int value)
    {
        for (int i = place; i < bitArr.size(); i += lowbit(i)) {
            bitArr[i] += value;
        }
    }

    int internalQuery(int place)
    {
        int res = 0;
        for (int i = place; i; i -= lowbit(i)) {
            res += bitArr[i];
        }
        return res;
    }
};

template <typename T>
struct RangeFenwick {
    Fenwick<T> s, t;

    explicit RangeFenwick(int n_) : s(n_), t(n_) {}

    void add(int l, int r, const T& val)
    {
        s.add(l, val);
        s.add(r + 1, -val);
        t.add(l, val * (l - 1));
        t.add(r + 1, -val * r);
    }

    T get(int l, int r)
    {
        return internalQuery(r) - internalQuery(l - 1);
    }

    T internalQuery(int pos)
    {
        return s.internalQuery(pos) * pos - t.internalQuery(pos);
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

    RangeFenwick<int> tf(10);
    tf.add(2, 2, 2);
    cout << tf.internalQuery(3);
    return 0;
}