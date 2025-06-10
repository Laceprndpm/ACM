#include <cctype>
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
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    string s, t;
    cin >> s >> t;
    s.push_back('x');
    int i = 0, j = 0;
    while (i < s.size()) {
        if (s[i] == tolower(t[j])) {
            j++;
            if (j == 3) {
                cout << "Yes\n";
                return 0;
            }
        }
        i++;
    }
    cout << "No\n";
    return 0;
}