#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

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

constexpr int INF = 1e9;

template <class Info>
struct SegmentTree {
    vector<i64>  leftSon, rightSon;
    vector<Info> info;
    i64          cnt = 1;
    i64          n;

    void pull(int p)
    {
        info[p] = info[leftSon[p]] + info[rightSon[p]];
    }

    int newnode()
    {
        leftSon.emplace_back(0);
        rightSon.emplace_back(0);
        info.emplace_back(Info());
        return ++cnt;
    }

    void modify(i64 p, i64 l, i64 r, i64 x, const Info &v)
    {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        i64 mid = (r - l) / 2 + l;
        if (x < mid) {
            if (leftSon[p] == 0) {
                leftSon[p] = newnode();
            }
            modify(leftSon[p], l, mid, x, v);
        } else {
            if (rightSon[p] == 0) {
                rightSon[p] = newnode();
            }
            modify(rightSon[p], mid, r, x, v);
        }
        pull(p);
    }

    Info rangeQuery(i64 p, i64 l, i64 r, i64 x, i64 y)
    {

        if (l >= y || r <= x || p == 0) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        i64 m = (r - l) / 2 + l;
        return rangeQuery(leftSon[p], l, m, x, y) + rangeQuery(rightSon[p], m, r, x, y);
    }

    SegmentTree(i64 n_) : n(n_)
    {
        leftSon.assign(2, 0);
        rightSon.assign(2, 0);
        info.assign(2, Info());
    }

    void modify(i64 x, const Info &value)
    {
        modify(1, 0, n, x, value);
    }

    Info rangeQuery(i64 l, i64 r)
    {
        return rangeQuery(1, 0, n, l, r);
    }
};

struct Info {
    i64 num = 0;
};

Info operator+(const Info &a, const Info &b)
{
    return {a.num + b.num};
}

signed main(signed argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // int
    int n;
    cin >> n;
    vector<i64> arrA(n), arrB(n);
    for (int i = 0; i < n; i++) {
        cin >> arrA[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> arrB[i];
    }
    SegmentTree<Info> segA((i64)1e9 + (i64)1e5);
    SegmentTree<Info> segB((i64)1e9 + (i64)1e5);
    for (int i = 0; i < n; i++) {
        int x = segA.rangeQuery(arrA[i], arrA[i] + 1).num;
        segA.modify(arrA[i], {x + 1});
        int y = segB.rangeQuery(arrB[i], arrB[i] + 1).num;
        segB.modify(arrB[i], {y + 1});
    }
    i64 ans = 0;
    for (int i = 0; i < n; i++) {  // A
        i64 tmp  = 0;
        i64 lenA = log10(arrA[i]) + 1;
        tmp += segB.rangeQuery(0, arrA[i] + 1).num * lenA;
        i64 remainPart = 1;
        for (int j = 0; j < lenA; j++) {
            remainPart *= 10ll;
        }
        tmp += segB.rangeQuery(remainPart - arrA[i], arrA[i] + 1).num;
        ans += tmp;
    }
    for (int i = 0; i < n; i++) {  // A
        i64 tmp  = 0;
        i64 lenB = log10(arrB[i]) + 1;
        tmp += segA.rangeQuery(0, arrB[i]).num * lenB;
        i64 remainPart = 1;
        for (int j = 0; j < lenB; j++) {
            remainPart *= 10ll;
        }
        tmp += segA.rangeQuery(remainPart - arrB[i], arrB[i]).num;
        ans += tmp;
    }

    cout << ans << '\n';
    // 三部分，一部分为<进位所需
    // 进不到nxt
    // 二部分是刚刚好可以进位到nxt
    // 三部分是直接大一位
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */