#include <bits/stdc++.h>

#include <ostream>
#include <vector>
using namespace std;

#define int  long long
#define endl '\n'
#define ll   long long

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

    bool operator!=(const F& o) const
    {
        return !(*this == o);
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

bool cmp(F x, F y)
{
    return F(abs(x)) < F(abs(y));
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<F> arr(n);
        for (int i = 0; i <= n - 1; i++) {
            double brr;
            cin >> brr;
            arr[i] = brr;
        }

        sort(arr.begin(), arr.end(), cmp);
        int z1 = 0, z2 = 0;
        for (int i = 0; i <= n - 1; i++) {
            if (arr[i] < F(0)) {
                z1++;
            } else {
                z2++;
            }
        }
        if (F(abs(arr[0])) == F(abs(arr[n - 1]))) {
            if ((abs(z1 - z2)) <= 1 || (z1 == 0 || z2 == 0)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
            continue;
        }
        F    cha = arr[1] / arr[0];
        bool tmp = true;
        for (int i = 2; i <= n - 1; i++) {
            F res = (F)arr[i] / arr[i - 1];
            if (res != cha) {
                tmp = false;
                break;
            }
        }
        if (tmp == false) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}