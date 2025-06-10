#include <algorithm>
#include <functional>
#include <vector>
#define REMOVE_ME
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
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) {
        cin >> i;
    }
    vector<int> org(arr);
    sort(arr.begin(), arr.end(), greater<>());
    for (int i = 0; i < n; i++) {
        cout << lower_bound(arr.begin(), arr.end(), org[i], greater<>()) - arr.begin() + 1 << '\n';
    }
    return 0;
}