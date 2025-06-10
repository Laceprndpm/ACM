#include <algorithm>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
i64           n, p, q;

struct node {
    i64 x, y;

    bool operator<(const node& t) const
    {
        if (x != t.x) {
            return x < t.x;
        }
        return y < t.y;
    }
};

int gcd(int a, int b)
{
    return b==0?a:gcd(b,a%b);
}
i64 work(const vector<node>& arr)
{
    node last{p, 0};
    i64  ans = 0;
    for (const node& i : arr) {
        ans += (last.x - i.x + 1) * (q - i.y + 1);
        last = i;
        last.x--;
        last.y--;
    }
    return ans;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 10);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int l = 0, r = 0;
    vector<int> b(n + 10);
    for (int i = 1; i + 1<= n; i++) {
        b[i]=a[i+1]-a[i];
    }
    for (int i = 1; i <= n-1; i++) {
        if (b[i] == -k) {
            l = i+1;
            break;
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        if (b[i] == k) {
            r = i;
            break;
        }
    }
    if (l != 0 && r != 0) {
        for(int i=l;i<=r;i++)a[i]+=k;
    }
    int ans = a[1];
    for (int i = 1; i <= n; i++) {
        ans=gcd(ans,a[i]);
    }
    cout<<ans<<'\n';

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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}