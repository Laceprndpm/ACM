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
    vector<int> arr{1, 1};
    int         a = 1, b = 1;
    while (arr.back() < 20211001) {
        arr.emplace_back(a + b);
        a = b;
        b = arr.back();
    }
    cout << arr.size();
    return 0;
}