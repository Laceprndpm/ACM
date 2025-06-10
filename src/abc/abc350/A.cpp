#include <iostream>
#include <string>
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
    string sub(s.begin() + 3, s.end());
    int    num = stoi(sub);
    if (num >= 1 && num <= 349 && num != 316) {
        cout << "Yes\n";
        return 0;
    }
    cout << "No\n";
    return 0;
}