#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
i64           k;

i64 dist(const pair<i64, i64>& s, const pair<i64, i64>& e)
{
    if (k == 2) {
        i64 deltaX = abs(s.first - e.first);
        i64 deltaY = abs(s.second - e.second);

        return 2ll * (min(deltaX, deltaY)) + 3 * (max(deltaX, deltaY) - min(deltaX, deltaY)) / 2;
    }
    return 2ll * max(abs(s.first - e.first), abs(s.second - e.second));
}

i64 sb_dist(const pair<i64, i64>& s, const pair<i64, i64>& e)
{
    i64 bSx = s.first / k;
    i64 bSy = s.second / k;
    if (bSx == e.first && bSy == e.second) {
        return 0;
    }
    if (bSx != e.first) {  // x不同
        if (bSx < e.first) {
            return e.first * k - s.first;
        } else {
            return s.first - (e.first * k + k - 1);
        }
    }
    if (bSy != e.second) {  // y不同
        if (bSy < e.second) {
            return e.second * k - s.second;
        } else {
            return s.second - (e.second * k + k - 1);
        }
    }
    assert(0);
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
    // 可以观察到，当进入某一块大型瓷砖后，就可以以某种方式运动到目标附近的大型瓷砖
    // 似乎有十六倍的常数。。。可以接受吗？
    // 特判在同一块小瓷砖的情况哦
    // 可以以2cost来进行斜向移动呢
    // SP:k == 2，可以直接以3的代价横穿小格
    i64 ans = INT64_MAX;
    cin >> k;
    i64 Sx, Sy, Tx, Ty;
    cin >> Sx >> Sy >> Tx >> Ty;
    Sx += 4 * k;
    Sy += 4 * k;
    Tx += 4 * k;
    Ty += 4 * k;
    i64 bSx = Sx / k, bSy = Sy / k, bTx = Tx / k, bTy = Ty / k;
    if (k == 1) {
        cout << abs(Sx - Tx) + abs(Sy - Ty);
        return 0;
    }
    if (bSx == bTx && bSy == bTy) {
        ans = abs(Sx - Tx) + abs(Sy - Ty);
    }
    vector<pair<i64, i64>> sVector;
    vector<pair<i64, i64>> eVector;
    if ((bSx + bSy) % 2 == 0) {  // small
        sVector.push_back({bSx - 1, bSy});
        sVector.push_back({bSx + 1, bSy});
        sVector.push_back({bSx, bSy - 1});
        sVector.push_back({bSx, bSy + 1});
    } else {
        sVector.push_back({bSx, bSy});
    }
    if ((bTx + bTy) % 2 == 0) {
        eVector.push_back({bTx - 1, bTy});
        eVector.push_back({bTx + 1, bTy});
        eVector.push_back({bTx, bTy - 1});
        eVector.push_back({bTx, bTy + 1});
    } else {
        eVector.push_back({bTx, bTy});
    }
    for (auto s : sVector) {
        for (auto e : eVector) {
            i64 curtotal = 0;
            curtotal += sb_dist({Sx, Sy}, s);
            curtotal += sb_dist({Tx, Ty}, e);
            curtotal += dist(s, e);
            ans = min(curtotal, ans);
        }
    }
    cout << ans << '\n';
    return 0;
}