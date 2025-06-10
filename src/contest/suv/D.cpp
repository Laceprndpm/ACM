#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
using i128        = __int128;

istream& operator>>(istream& in, i128& num)
{
    string s;
    in >> s;
    num      = 0;
    bool neg = (s[0] == '-');
    for (size_t i = neg; i < s.size(); ++i) {
        num = num * 10 + (s[i] - '0');
    }
    if (neg) num = -num;
    return in;
}

ostream& operator<<(ostream& out, const i128& num)
{
    if (num == 0) {
        return out << '0';
    }
    i128 temp = num;
    if (temp < 0) {
        out << '-';
        temp = -temp;
    }
    string result;
    while (temp > 0) {
        result += char('0' + temp % 10);
        temp /= 10;
    }
    reverse(result.begin(), result.end());
    return out << result;
}

void solve()
{
    i128 p, a, b;
    i128 q, c, d;
    i128 m, t;
    cin >> p >> a >> b;
    cin >> q >> c >> d;
    cin >> m >> t;
    i128 pro_bag = q - p;
    i128 curTime = 0;

    i128 Kt = a + c;
    i128 Bt = b + d;
    {
        i128 cur_bags = m / p;
        if (cur_bags == 0) {
            cout << m << '\n';
            return;
        };
    }
    while (true) {
        // cout << "m:" << m << '\n';
        i128 cur_bags   = m / p;
        i128 money_time = pro_bag * cur_bags;
        i128 times      = ((cur_bags + 1) * p - m + money_time - 1) / (money_time);
        i128 needtime   = times * cur_bags * Kt + times * Bt;
        // cout << "needtime:" << needtime << '\n';
        if (needtime + curTime > t) {
            if (times != 1) {
                i128                 left  = 0;
                i128                 right = times;
                function<bool(i128)> check = [&](i128 u) -> bool {
                    return u * Kt * cur_bags + u * Bt + curTime <= t;
                };
                while (left < right) {
                    i128 mid = (right - left) / 2 + left + 1;
                    if (check(mid)) {
                        left = mid;
                    } else {
                        right = mid - 1;
                    }
                }
                i128 needtime = left * cur_bags * Kt + left * Bt;
                curTime += needtime;
                m += money_time * left;
            }
            break;
        } else {
            curTime += needtime;
            m += times * money_time;
        }
    }
    i128 remainTime = t - curTime;
    if (remainTime > Bt) {
        i128 maybags    = min((remainTime - Bt) / Kt, m / p);
        i128 still_bags = max(maybags, (i128)0);
        m += still_bags * pro_bag;
    }
    cout << m << '\n';
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
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}