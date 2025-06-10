#include <algorithm>
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int i = s.size() - 1;
        while (s[i] == '0') {
            i--;
        }
        cout << s.size() - count(s.begin(), s.end(), '0') - 2 + (s.size() - i) << '\n';
    }
    return 0;
}