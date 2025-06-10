#include <iostream>
#include <map>
#include <string>
#include <utility>
using namespace std;
using i64       = long long;
constexpr i64 z = (1ll << 31);

template <class T>
T qpow(T base, i64 q)
{
    T ans = 1;
    while (q) {
        if (q & 1) {
            ans *= base;
        }
        if (base >= z || ans >= z) {
            return z;
        }
        base *= base;
        q >>= 1;
    }
    return ans;
}

string factory(i64 base, i64 q)
{
    string ans = "";
    for (int i = 1; i <= base; i++) {
        ans += to_string(i);
        ans += '^';
        ans += to_string(q);
        if (i != base) {
            ans += "+";
        }
    }
    return ans;
}

int main()
{
    map<i64, pair<i64, i64>> mp;
    for (i64 q = 1; q <= 31; q++) {
        i64 cur = 0;
        for (i64 i = 1;; i++) {
            cur += qpow(i, q);
            mp[cur] = {i, q};
            if (cur >= z) {
                break;
            }
        }
    }
    int n;
    cin >> n;
    if (mp.count(n) == 0) {
        printf("Impossible for %d.\n", n);
        return 0;
    }
    cout << factory(mp[n].first, mp[n].second);
    return 0;
}