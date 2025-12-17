#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
using ll  = long long;
using i64 = long long;

// vectors
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()
#define mt      make_tuple
#define fi      first
#define se      second

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> arr(n);
    for (int i = 0, l, r; i < n; i++) {
        cin >> l >> r;
        arr[i] = {l, r};
    }
    sort(all(arr), [](auto a, auto b) { return a.fi < b.fi; });
    priority_queue<int, vector<int>, greater<>> pq;

    i64 cnt = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        while (!pq.empty() && pq.top() < arr[i].fi) pq.pop(), cnt--;
        ans += cnt++;
        pq.push(arr[i].se);
    }
    cout << ans << '\n';
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
