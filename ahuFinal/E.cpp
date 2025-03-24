#include <algorithm>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct node {
    i64 s, a, e;
    i64 sum;

    bool operator<(const node& t) const
    {
        if (sum != t.sum) return sum < t.sum;
        return e > t.e;
    }
};

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
    vector<node> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].s >> arr[i].a >> arr[i].e;
        arr[i].sum = arr[i].s + arr[i].a + arr[i].e;
    }
    sort(arr.begin() + 1, arr.end());
    i64 curtime = 0;
    i64 ans     = 0;
    for (int i = 1; i <= n; i++) {
        curtime += arr[i].s + arr[i].a;
        ans += curtime;
        curtime += arr[i].e;
    }
    cout << ans << endl;
    return 0;
}