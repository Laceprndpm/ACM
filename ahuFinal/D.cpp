#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
vector<int>   dp;

struct Tag {
    i64 x = 0;

    void apply(const Tag &t) &
    {
        if (dp[x] < dp[t.x]) {
            x = t.x;
        } else if (dp[x] == dp[t.x])
            x = min(x, t.x);
    }
};

struct Info {
    i64 x = 0;

    void apply(const Tag &t) &
    {
        if (dp[x] < dp[t.x]) {
            x = t.x;
        } else if (dp[x] == dp[t.x])
            x = min(x, t.x);
    }
};

Info operator+(const Info &a, const Info &b)
{
    if (dp[a.x] > dp[b.x])
        return a;
    else if (dp[a.x] < dp[b.x])
        return b;
    else {
        Info temp;
        temp.x = min(a.x, b.x);
        return temp;
    }
}

struct LazySegmentTree {
    int          n;
    vector<Info> info;
    vector<Tag>  tag;
    vector<i64>  leftB;
    vector<i64>  rightB;

    LazySegmentTree() : n(0) {}

    LazySegmentTree(int _n, Info _v = Info())
    {
        init(_n, _v);
    }

    void init(int _n, Info _v = Info())
    {
        init(vector<Info>(_n, _v));
    }

    void init(vector<Info> _init)
    {
        n = _init.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
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
        build(1, 0, n);
    }

    void pull(int p)
    {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void apply(int p, const Tag &v)
    {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push(int p)
    {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }

    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (r == l) {
            info[p] = v;
            return;
        }
        int m = (r - l) / 2 + l;
        push(p);
        if (x <= m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v)
    {
        modify(1, 0, n, p, v);
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
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
    }

    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, 0, n, l, r);
    }

    void rangeApply(int p, int l, int r, int x, int y, const Tag &v)
    {
        if (l > y || r < x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (r - l) / 2 + l;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeApply(int l, int r, const Tag &v)
    {
        return rangeApply(1, 0, n, l, r, v);
    }
};

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    string input;
    cin >> input;
    vector<string> names;
    int            nLen = input.length();
    int            i = 0, j = 0;
    for (i = 1; i < nLen; i++) {
        if (isupper(input[i])) {
            names.emplace_back(string(input.begin() + j, input.begin() + i));
            j = i;
        }
    }
    names.emplace_back(string(input.begin() + j, input.begin() + i));
    vector<string> string2int(names);
    sort(string2int.begin(), string2int.end());
    string2int.erase(unique(string2int.begin(), string2int.end()), string2int.end());
    map<string, int> int2string;
    for (int i = 1; i <= string2int.size(); i++) {
        int2string[string2int[i - 1]] = i;
    }
    dp.resize(int2string.size() + 1);
    LazySegmentTree lzt(int2string.size() + 1);
    vector<int>     save(int2string.size() + 1);
    int             maxidx = 0;
    int             maxval = 0;
    for (int i = 0; i < names.size(); i++) {
        int cur   = int2string[names[i]];
        int last  = lzt.rangeQuery(1, cur - 1).x;
        dp[cur]   = dp[last] + 1;
        save[cur] = last;
        Info temp;
        temp.x = cur;
        lzt.modify(cur, temp);
        if (dp[cur] > maxval || ((dp[cur] == maxval) && maxidx > cur)) {
            maxval = dp[cur];
            maxidx = cur;
        }
    }
    stack<string> st;
    for (int i = maxidx; i != 0; i = save[i]) {
        st.push(string2int[i - 1]);
    }
    while (!st.empty()) {
        cout << st.top();
        st.pop();
    }
    return 0;
}