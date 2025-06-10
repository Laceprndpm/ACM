#include <iostream>
#include <map>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

bool check(string s)
{
    int n = s.size();
    if (n % 2) return false;
    map<char, int> mp;
    for (int i = 0; i < n / 2; i++) {
        if (s[i * 2] != s[i * 2 + 1]) {
            return false;
        }
        mp[s[i * 2]]++;
        if (mp[s[i * 2]] != 1) {
            return false;
        }
    }
    return true;
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
    string s;
    cin >> s;
    if (check(s)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}