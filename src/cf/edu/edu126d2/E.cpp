#include <cassert>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct Info {
    int  l;
    bool l_had{false};
    int  r;
    bool r_had{false};
    bool macaroni{false};
    int  connectNum = 0;
    bool empty{true};
};

Info operator+(const Info &a, const Info &b)
{
    if (a.empty) {
        return b;
    }
    if (b.empty) {
        return a;
    }
    Info sum;
    sum.empty = false;
    sum.l     = a.l;
    sum.r     = b.r;
    if (a.l == 5) sum.l_had = a.l_had;
    if (b.r == 5) sum.r_had = b.r_had;
    sum.macaroni = (a.macaroni && b.macaroni);
    if ((a.r != 5 && b.l != 5) || ((a.r == 5) && (b.l != 5) && (b.l != 7))
        || ((b.l == 5) && (a.r != 5) && (a.r != 7))) {
        if (a.r & b.l) {
            sum.connectNum = a.connectNum + b.connectNum - 1;
        } else {
            sum.connectNum = a.connectNum + b.connectNum;
        }
        return sum;
    }
    if (a.r == 5) {
        if (a.r_had) {
            if (b.l == 5) {
                if (b.l_had) {
                    sum.connectNum = a.connectNum + b.connectNum - 1;
                } else {
                    sum.connectNum = a.connectNum + b.connectNum - 2;
                    if (b.macaroni) {
                        sum.r_had = true;
                    }
                }
            } else if (b.l == 7) {
                sum.connectNum = a.connectNum + b.connectNum - 1;
            } else {
                assert(0);
            }
        } else {
            if (b.l == 5) {
                if (b.l_had) {
                    sum.connectNum = a.connectNum + b.connectNum - 2;
                    if (a.macaroni) {
                        sum.l_had = true;
                    }
                } else {
                    sum.connectNum = a.connectNum + b.connectNum - 2;
                }
            } else if (b.l == 7) {
                sum.connectNum = a.connectNum + b.connectNum - 2;
                if (a.macaroni) {
                    sum.l_had = true;
                }
            } else {
                assert(0);
            }
        }
    } else if (b.l == 5) {  // a!=5
        assert(a.r == 7);
        if (b.l_had) {
            sum.connectNum = a.connectNum + b.connectNum - 1;
        } else {
            sum.connectNum = a.connectNum + b.connectNum - 2;
            if (b.macaroni) {
                sum.r_had = true;
            }
        }
    }
    return sum;
}

// template from jiangly
struct LazySegmentTree {
    int          n;
    vector<Info> info;
    vector<i64>  leftB;
    vector<i64>  rightB;

    LazySegmentTree() : n(0) {}

    LazySegmentTree(int _n, Info _v = Info())
    {
        init(_n, _v);
    }

    template <class T>
    LazySegmentTree(vector<T> _init)
    {
        init(_init);
    }

    void init(int _n, Info _v = Info())
    {
        init(vector(_n, _v));
    }

    template <class T>
    void init(vector<T> _init)
    {
        n = _init.size() - 1;
        info.assign(4 << __lg(n), Info());
        leftB.resize(4 << __lg(n));
        rightB.resize(4 << __lg(n));
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            leftB[p]  = l;
            rightB[p] = r;
            if (r == l) {
                info[p] = _init[l];
                return;
            }
            int m = (r - l) / 2 + l;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }

    void pull(int p)
    {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= x && r <= y) {
            return info[p];
        }
        if (l > y || r < x) {
            return Info();
        }
        int m = (r - l) / 2 + l;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
    }

    Info rangeQuery(int l, int r)
    {
        if (l > r) {
            return Info();
        }
        return rangeQuery(1, 1, n, l, r);
    }
};

// Removed operator= function as it should be a member function

signed main(int argc, char **argv)
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
    vector<Info> arr(n + 1);
    string       a, b, c;
    string       em{""};
    cin >> a >> b >> c;
    a = ' ' + a;
    b = ' ' + b;
    c = ' ' + c;
    for (int i = 1; i <= n; i++) {
        string cur = "";
        cur += a[i];
        cur += b[i];
        cur += c[i];
        int dec         = stoi(cur, nullptr, 2);
        arr[i].l        = dec;
        arr[i].r        = dec;
        arr[i].empty    = false;
        arr[i].macaroni = (dec == 5);
        if (dec == 5) {
            arr[i].connectNum = 2;
        } else if (dec != 0) {
            arr[i].connectNum = 1;
        } else {
            arr[i].connectNum = 0;
        }
    }
    LazySegmentTree lzt(arr);
    int             q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << lzt.rangeQuery(l, r).connectNum << '\n';
    }
    return 0;
}