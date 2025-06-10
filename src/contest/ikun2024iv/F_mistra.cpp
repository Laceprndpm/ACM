#include <iostream>
#include <ranges>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<i64, i64>;
constexpr i64 INF = 1e9;

#pragma GCC   optimize(2)
// #pragma GCC   target("avx")
// #pragma GCC   optimize("Ofast")
#pragma GCC optimize("inline")
// #pragma GCC   optimize("-fgcse")
// #pragma GCC   optimize("-fgcse-lm")
// #pragma GCC   optimize("-fipa-sra")
// #pragma GCC   optimize("-ftree-pre")
// #pragma GCC   optimize("-ftree-vrp")
// #pragma GCC   optimize("-fpeephole2")
// #pragma GCC   optimize("-ffast-math")
// #pragma GCC   optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
// #pragma GCC   optimize("-falign-jumps")
// #pragma GCC   optimize("-falign-loops")
// #pragma GCC   optimize("-falign-labels")
// #pragma GCC   optimize("-fdevirtualize")
// #pragma GCC   optimize("-fcaller-saves")
// #pragma GCC   optimize("-fcrossjumping")
// #pragma GCC   optimize("-fthread-jumps")
// #pragma GCC   optimize("-funroll-loops")
// #pragma GCC   optimize("-fwhole-program")
// #pragma GCC   optimize("-freorder-blocks")
// #pragma GCC   optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
// #pragma GCC   optimize("-ftree-tail-merge")
// #pragma GCC   optimize("-fschedule-insns2")
// #pragma GCC   optimize("-fstrict-aliasing")
// #pragma GCC   optimize("-fstrict-overflow")
// #pragma GCC   optimize("-falign-functions")
// #pragma GCC   optimize("-fcse-skip-blocks")
// #pragma GCC   optimize("-fcse-follow-jumps")
// #pragma GCC   optimize("-fsched-interblock")
// #pragma GCC   optimize("-fpartial-inlining")
// #pragma GCC   optimize("no-stack-protector")
// #pragma GCC   optimize("-freorder-functions")
// #pragma GCC   optimize("-findirect-inlining")
// #pragma GCC   optimize("-fhoist-adjacent-loads")
// #pragma GCC   optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
// #pragma GCC   optimize("-ftree-switch-conversion")
// #pragma GCC   optimize("-foptimize-sibling-calls")
// #pragma GCC   optimize("-fexpensive-optimizations")
// #pragma GCC   optimize("-funsafe-loop-optimizations")
// #pragma GCC   optimize("inline-functions-called-once")
// #pragma GCC   optimize("-fdelete-null-pointer-checks")
// #pragma GCC   optimize(2)

i64 pos1, pos2, ti1, ti2;
i64 status = 0, laPos, laTi;
i64 v;

vector<pair<i64, vector<i64>>> mp;

bool is_in1(i64 pos, i64 t)
{
    i64 l = pos1 - (t - ti1) * v, r = pos1 + (t - ti1) * v;
    return (l <= pos && pos <= r);
}

bool is_in2(i64 pos, i64 t)
{
    i64 l = pos2 - (t - ti2) * v, r = pos2 + (t - ti2) * v;
    return (l <= pos && pos <= r);
};

bool is_inla(i64 pos, i64 t)
{
    i64 l = laPos - (t - laTi) * v, r = laPos + (t - laTi) * v;
    return (l <= pos && pos <= r);
};

bool check(void)
{
    status          = 0;
    auto it         = mp.begin();
    auto [ft, fpos] = *it;
    if (fpos.size() == 2) {
        pos1 = fpos[0];
        ti1  = ft;
        pos2 = fpos[1];
        ti2  = ft;
    } else {
        ti1  = ft;
        pos1 = fpos[0];
        for (it++; it != mp.end(); it++) {
            auto [t, pos] = *it;
            if (pos.size() == 2) {
                i64 tar1 = pos[0], tar2 = pos[1];
                if (is_in1(tar1, t) || is_in1(tar2, t)) {
                    pos1 = tar1, pos2 = tar2;
                    ti1 = t, ti2 = t;
                    break;
                } else {
                    return false;
                }
            } else {
                if (is_in1(pos[0], t)) {
                    pos1 = pos[0];
                    ti1  = t;
                    continue;
                } else {
                    pos2 = pos[0];
                    ti2  = t;
                    break;
                }
            }
        }
    }
    if (it == mp.end()) {
        return true;
    }
    for (it++; it != mp.end(); it++) {
        auto [t, pos] = *it;
        if (pos.size() == 2) {
            i64 tar1 = pos[0], tar2 = pos[1];
            if (status) {
                if ((is_inla(tar1, t) && (is_in1(tar2, t) || is_in2(tar2, t)))
                    || (is_inla(tar2, t) && (is_in1(tar1, t) || is_in2(tar1, t)))) {
                    pos1 = tar1, ti1 = t, pos2 = tar2, ti2 = t;
                    status = 0;
                } else {
                    return false;
                }
            } else {
                if ((is_in1(tar1, t) && is_in2(tar2, t)) || (is_in2(tar1, t) && is_in1(tar2, t))) {
                    pos1 = tar1, ti1 = t, pos2 = tar2, ti2 = t;
                } else {
                    return false;
                }
            }
        } else {
            i64 tar = pos[0];
            if (status) {
                if (is_in1(tar, t) && is_in2(tar, t)) {
                    if (is_inla(tar, t)) {
                        laPos = tar, laTi = t;
                    } else {
                        pos1 = laPos, ti1 = laTi;
                        pos2 = tar, ti2 = t;
                        status = 0;
                    }
                    continue;
                }
                if (is_in1(tar, t) || is_in2(tar, t)) {
                    pos1 = tar, ti1 = t;
                    pos2 = laPos, ti2 = laTi;
                    status = 0;
                    continue;
                } else {
                    return false;
                }
            } else {
                if (is_in1(tar, t) && is_in2(tar, t)) {
                    status = 1;
                    laPos = tar, laTi = t;
                    continue;
                }
                if (is_in1(tar, t)) {
                    pos1 = tar, ti1 = t;
                } else if (is_in2(tar, t)) {
                    pos2 = tar, ti2 = t;
                } else {
                    return false;
                }
            }
        }
    }
    return true;
};

void solve()
{

    mp.clear();
    i64 n;
    cin >> n;
    for (i64 i = 0, j = 0; i < n; i++, j++) {
        i64 time, p;
        cin >> time >> p;
        if (j && mp[j - 1].first == time) {
            j--;
            mp[j].second.emplace_back(p);
        } else {
            mp.push_back({time, {p}});
        }
    }
    for (auto [_, vec] : mp) {
        if (vec.size() > 2) {
            cout << -1 << '\n';
            return;
        }
    }
    i64 l = 0, r = (i64)(1e9) + 1;
    i64 ans;
    while (l <= r) {
        i64 mid = (r + l) / 2;
        v       = mid;
        if (check()) {
            ans = mid;
            r   = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << '\n';
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
    i64 t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}