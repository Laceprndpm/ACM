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
    int    n;
    char   c1, c2;
    string s;
    cin >> n >> c1 >> c2;
    cin >> s;
    for (char& c : s) {
        if (c != c1) {
            c = c2;
        }
    }
    cout << s;
    return 0;
}