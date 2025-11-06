#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
constexpr int MOD = 998244353;

// using i128        = __int128;
// #define i64 i128

// istream& operator>>(istream& in, i128& num)
// {
//     string s;
//     in >> s;
//     num      = 0;
//     bool neg = (s[0] == '-');
//     for (size_t i = neg; i < s.size(); ++i) {
//         num = num * 10 + (s[i] - '0');
//     }
//     if (neg) num = -num;
//     return in;
// }

// ostream& operator<<(ostream& out, const i128& num)
// {
//     if (num == 0) {
//         return out << '0';
//     }
//     i128 temp = num;
//     if (temp < 0) {
//         out << '-';
//         temp = -temp;
//     }
//     string result;
//     while (temp > 0) {
//         result += char('0' + temp % 10);
//         temp /= 10;
//     }
//     reverse(result.begin(), result.end());
//     return out << result;
// }

i64 qpow(i64 n, i64 q, i64 mod = MOD)
{
    if (q == 0) {
        return 1;
    }
    i64 ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
            ans %= mod;
        }
        n *= n;
        n %= mod;
        q >>= 1;
    }
    return ans;
}

void solve()
{
    map<i64, i64> mp;
    i64           n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        i64 w, num;
        cin >> num >> w;
        mp[w] += num;
    }
    for (auto it = mp.begin(); it != mp.end(); it++) {
        auto& [w, num] = *it;
        if (num >= m) {
            i64 r = (num - m + 1) / 2;
            num -= r * 2;
            if (mp.count(w + 1) != 0) {
                mp[w + 1] += r;
            } else {
                mp.insert({w + 1, r});
            }
        }
    }
    i64 remain = 0;
    i64 ans    = 0;
    for (auto it = mp.rbegin(); it != mp.rend(); it++) {
        if (it != mp.rbegin()) {
            if (prev(it)->first - it->first >= 31 && remain) {
                break;
            }
            remain *= (1ll << (prev(it)->first - it->first));
            if (remain >= (i64)2e9) {
                break;
            }
        }
        remain -= it->second;
        if (remain < 0) {
            remain += m;
            ans += qpow(2, it->first);
            ans %= MOD;
        }
    }
    cout << ans << '\n';
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}