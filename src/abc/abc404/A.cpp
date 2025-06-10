#include <iostream>
#include <set>
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
    multiset<char> mt;
    for (char c = 'a'; c <= 'z'; c++) {
        mt.insert(c);
    }
    for (char c : s) {
        mt.extract(c);
    }
    cout << *mt.begin();
    return 0;
}