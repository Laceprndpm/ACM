#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

int check(const vector<int>& arr)
{
    int cnt  = 0;
    int mx   = -1;
    int n    = arr.size();
    int last = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] != last) {
            last = arr[i];
            cnt  = 1;
        } else {
            cnt++;
        }
        mx = max(mx, cnt);
    }
    return mx;
}

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
    int mx = 1;
    for (int i = 1; i < n; i++) {
        for (int k = 0; k < i; k++) {
            vector<int> cur;
            for (int j = k; j < n; j += i) {
                cur.push_back(arr[j]);
            }
            mx = max(mx, check(cur));
        }
    }
    cout << mx << '\n';
    return 0;
}