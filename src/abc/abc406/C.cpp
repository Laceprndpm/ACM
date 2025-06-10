#include <functional>
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
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<i64> brr;
    int         i = 0;
    while (i + 1 < n && arr[i + 1] < arr[i]) {
        i++;
    }
    for (; i + 1 < n;) {
        int j = i;
        while (j + 1 < n && arr[j + 1] > arr[j]) {
            j++;
        }
        brr.push_back(j - i + 1);
        while (j + 1 < n && arr[j + 1] < arr[j]) {
            j++;
        }
        i = j;
    }
    i64 ans = 0;
    for (int i = 0; i + 1 < brr.size(); i++) {
        ans += (brr[i] - 1) * (brr[i + 1] - 1);
    }
    cout << ans << '\n';
    return 0;
}