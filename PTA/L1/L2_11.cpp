#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

struct SegmentTree {
    int         n;
    vector<int> maxvalue;
    vector<int> tag;

    void pull(int p)
    {
        maxvalue[p] = max(maxvalue[p * 2], maxvalue[p * 2 + 1]);
    }

    void push(int p)
    {
        maxvalue[p * 2] += tag[p];
        tag[p * 2] += tag[p];
        maxvalue[p * 2 + 1] += tag[p];
        tag[p * 2 + 1] += tag[p];
        tag[p] = 0;
    };

    SegmentTree(int n_) : n(n_), maxvalue((n_ + 1) * 4 + 5), tag((n_ + 1) * 4 + 5) {}

    void rangeApply(int p, int l, int r, int x, int y)
    {
        if (l > y || r < x) return;
        if (l == r) {
            maxvalue[p] += 1;
            return;
        }
        if (l >= x && r <= y) {
            maxvalue[p] += 1;
            tag[p]++;
            return;
        }
        int mid = (l + r) / 2;
        push(p);
        if (x <= mid) {
            rangeApply(p * 2, l, mid, x, y);
        }
        if (y > mid) {
            rangeApply(p * 2 + 1, mid + 1, r, x, y);
        }
        pull(p);
        return;
    }

    int rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l > y || r < x) return 0;
        if (l == r) return maxvalue[p];
        int ans = 0;
        if (l >= x && r <= y) {
            return maxvalue[p];
        }
        int mid = (l + r) / 2;
        push(p);
        if (x <= mid) {
            ans = max(ans, rangeQuery(p * 2, l, mid, x, y));
        }
        if (y > mid) {
            ans = max(ans, rangeQuery(p * 2 + 1, mid + 1, r, x, y));
        }
        return ans;
    }

    int rangeQuery(int x, int y)
    {
        return rangeQuery(1, 1, n, x, y);
    }

    void rangeApply(int x, int y)
    {
        rangeApply(1, 1, n, x, y);
    }
};

int trans(string s)

{
    int t = 1;
    t += (s[0] - '0') * 60 * 60 * 10;
    t += (s[1] - '0') * 60 * 60;
    t += (s[3] - '0') * 60 * 10;
    t += (s[4] - '0') * 60;
    t += (s[6] - '0') * 10;
    t += (s[7] - '0');
    return t;
}

int main()

{
    int n;
    cin >> n;
    SegmentTree st(86400);
    for (int i = 0; i < n; i++) {
        string star, ed;
        cin >> star >> ed;
        int stT = trans(star), edT = trans(ed);
        st.rangeApply(stT, edT);
    }
    cout << st.rangeQuery(1, 86400);
    return 0;
}