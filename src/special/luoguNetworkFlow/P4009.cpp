#include <bits/stdc++.h>

#include <cstring>
#include <deque>
#include <limits>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

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

constexpr int N = 101, K = 11;
int           gas[N][N];
int           dx[] = {1, 0, -1, 0};
int           dy[] = {0, 1, 0, -1};
int           dist[K][N][N];

void solve()
{
    int n, k, a, b, c;
    cin >> n >> k >> a >> b >> c;
    memset(dist, 0x7f, sizeof dist);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> gas[i][j];
    }
    priority_queue<pair<int, tuple<int, int, int>>, vector<pair<int, tuple<int, int, int>>>, greater<>> pq;
    pq.push({0, {k, 1, 1}});
    auto isvalid = [&](int x, int y) { return x >= 1 && y >= 1 && x <= n && y <= n; };
    while (!pq.empty()) {
        auto [udist, postion] = pq.top();
        pq.pop();
        auto [uk, ux, uy] = postion;
        for (int i = 0; i < 4; i++) {
            int vdist = udist;
            if (i >= 2) {
                vdist += b;
            }
            int vx = ux + dx[i], vy = uy + dy[i];
            int vk = uk - 1;
            if (vk < 0) continue;
            if (!isvalid(vx, vy)) continue;
            if (gas[vx][vy] == 1) {
                vk = k;
                vdist += a;
            }
            if (dist[vk][vx][vy] > vdist) {
                dist[vk][vx][vy] = vdist;
                pq.push({vdist, {vk, vx, vy}});
            }
        }
        {
            int vx = ux, vy = uy;
            int vk    = k;
            int vdist = udist + c + a;
            if (dist[vk][vx][vy] > vdist) {
                dist[vk][vx][vy] = vdist;
                pq.push({vdist, {vk, vx, vy}});
            }
        }
    }
    int mncost = numeric_limits<int>::max();
    for (int i = 0; i <= k; i++) {
        mncost = min(mncost, dist[i][n][n]);
    }
    cout << mncost << '\n';
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
