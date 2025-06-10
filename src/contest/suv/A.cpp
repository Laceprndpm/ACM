#include <bits/stdc++.h>

#include <iostream>
using namespace std;
using i128 = __int128;
#define int i128
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

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
    int n, k;
    cin >> n >> k;
    vector<int> ti(n);
    vector<int> li(n);
    vector<int> wi(n);
    for (int i = 0; i < n; i++)
        cin >> ti[i] >> li[i] >> wi[i];
    int                 left  = 1;
    int                 right = (int)2.2e18;
    function<bool(int)> check = [&](const int mid) -> bool {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += mid / (ti[i] * li[i] + wi[i]) * li[i];
            ans += min((mid % (ti[i] * li[i] + wi[i])) / ti[i], li[i]);
        }
        return ans >= k;
    };
    while (left < right) {
        int mid = ((right - left) >> 1) + left;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    cout << right << '\n';
    return;
}

signed main(signed argc, char** argv)
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
    while (t--)
        solve();
    return 0;
}