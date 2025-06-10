#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int         N = 500013;
int               f[N], vis[N];
int               d[N];

void solve()
{
    ll n, l, x, y, k;
    cin >> n >> l >> x >> y >> k;
    //[n-l+1,n+1)
    n    = n - l + 1;
    ll v = 0;
    y++;
    vector<pair<ll, ll>> seg;
    //[,)这段的意思大概就是找到一些区间，满足这个区间内的数字异或上x之后小于y
    for (int i = 29; ~i; i--) {
        if (x >> i & 1) v ^= 1ll << i;
        if (y >> i & 1) seg.emplace_back(v, v + (1ll << i)), v ^= 1ll << i;
    }
    vector<ll> event = {0};
    //[0,l) [x,y)
    for (auto [x, y] : seg) {
        // 上述小于y的区间，其端点被x和y全部包括，由于范围是[0,l),所以有可能产生影响的点应该加入x-l和y-l
        event.push_back(x), event.push_back(y);
        if (x - l >= 0) event.push_back(x - l);
        if (y - l >= 0) event.push_back(y - l);
    }
    sort(event.begin(), event.end());  // 排序所有可能产生影响的点
    while (event.back() > n)
        event.pop_back();  // 删除不可能是答案的点
    event.push_back(n);    // 因为包括n,n是上界，所以应该作为可能端点的备选
    auto isc = [&](pair<ll, ll> x, pair<ll, ll> y) {  // 判断连续小于y的可能区间，和目前区间重叠的部分
        x.second = min(x.second, y.second), x.first = max(x.first, y.first);
        return max(0ll, x.second - x.first);
    };
    auto f = [&](ll p) {  // 判断以这个数字作为区间起始点，其会有多少个异或x后小于y的点数量
        pair<ll, ll> pr = {p, p + l};
        ll           rt = 0;
        for (auto s : seg)
            rt += isc(pr, s);
        return rt;
    };
    for (int i = 0; i + 1 < event.size(); i++) {  // 对于每个点开始判断
        ll p = event[i], q = event[i + 1], fp = f(p),
           fq = f(q);  // 首先分成一个区间[p,q]，fp为p点作为起始点异或x值小于y的点数量，fq同理
        if (fp <= k
            && fq >= k) {  // 需要注意因为端点有限，a^x小于/大于y，和(a+l)^x大于/小于y只在端点发生变化，所以非端点部分为连续的，即要么递增，要么递减
            cout
                << p + k - fp
                << '\n';  // fp小于等于k，fq大于等于，小于等于y的数量在[p,q]这个区间内在递增，而且因为连续，根据零点定理，左右符号相反，所以存在一个点w满足q>=w>=p，w点作为起始点异或后小于y的数量为k
            return;
        }
        if (fp >= k && fq <= k) {  // 下面同礼
            cout << p + fp - k << '\n';
            return;
        }
    }
    cout << -1 << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
}