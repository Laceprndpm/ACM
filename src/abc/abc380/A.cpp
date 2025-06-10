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
    string s;
    cin >> s;
    int ct1 = 0, ct2 = 0, ct3 = 0;
    for (char c : s) {
        if (c == '1') {
            ct1++;
        } else if (c == '2') {
            ct2++;
        } else if (c == '3') {
            ct3++;
        }
    }
    if (ct1 == 1 && ct2 == 2 && ct3 == 3) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}