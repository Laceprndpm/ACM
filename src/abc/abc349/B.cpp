#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

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
    map<int, int> cnt;
    for (int i = 0; i < 26; i++) {
        cnt[count(s.begin(), s.end(), i + 'a')]++;
    }
    for (auto [k, v] : cnt) {
        if (v != 2 && k != 0) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    return 0;
}