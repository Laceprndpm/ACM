#include <iostream>
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
    int         i = 0;
    vector<int> buff;
    for (char cur : s) {
        if (cur == '|') {
            if (i != 0) buff.push_back(i);
            i = 0;
        } else {
            i++;
        }
    }
    for (int i : buff) {
        cout << i << ' ';
    }
    return 0;
}