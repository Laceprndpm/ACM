#include <algorithm>
#include <iostream>
#include <tuple>
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
    int a, b, c;
    cin >> a >> b >> c;
    vector<int> arr{a, b, c};
    ranges::sort(arr);
    if (ranges::all_of(arr, [&](int x) {
            return x == arr[0];
        }))
        cout << "Yes\n";
    else {
        if (arr[0] + arr[1] == arr[2])
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    return 0;
}