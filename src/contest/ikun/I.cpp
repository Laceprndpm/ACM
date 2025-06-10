#define REMOVE_ME
#include <iostream>
#include <map>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    string s;
    cin >> s;
    int            n = s.size();
    map<char, int> mp;
    for (int i = 0; i < n; i++)
        mp[s[i]]++;
    if (mp.size() == 1) {
        cout << n / 2 << '\n';
        return;
    } else {
        string tmp = "";
        string now;
        for (int i = 0; i < n; i++) {
            if (s[i] == s.back()) {
                tmp.push_back(s[i]);
                continue;
            } else {
                now = s.substr(i);
                break;
            }
        }
        now += tmp;
        //cout<<now<<' ';
        int cnt  = 1;
        int ans  = 0;
        int flag = 0;
        for (int i = 1; i < n; i++) {
            if (now[i] == now[i - 1])
                cnt++;
            else {
                if (cnt >= 2) {
                    ans += cnt / 2;
                    if (cnt % 2 == 0) flag = 1;
                }
                cnt = 1;
            }
        }
        //cout<<cnt<<' ';
        if (cnt >= 2) {
            ans += cnt / 2;
            if (cnt % 2 == 0) flag = 1;
        }
        if (flag)
            cout << ans - 1 << '\n';
        else
            cout << ans << '\n';
    }
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
    while (t--)
        solve();
    return 0;
}