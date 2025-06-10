#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;

struct Node {
    int x, y, id, d;

    bool operator<(Node oth) const
    {
        if (x != oth.x) return x < oth.x;
        return id < oth.id;
    }
};

struct BIT {
    int tree[N];

    int lowbit(int x)
    {
        return x & -x;
    }

    void add(int p, int d)
    {
        while (p < N) {
            tree[p] += d;
            p += lowbit(p);
        }
    }

    int query(int p)
    {
        int ans = 0;
        while (p) {
            ans += tree[p];
            p -= lowbit(p);
        }
        return ans;
    }
} bit;

int          n, m;
int          ans[N];
vector<Node> vec;

signed main()
{
    scanf("%d%d", &n, &m);
    n *= 2;
    for (int i = 1; i <= m; i++) {
        int c, d;
        scanf("%d%d", &c, &d);
        // vec.push_back({c, d, -1, 1});
        // vec.push_back({d, c, -1, 1});

        vec.push_back({c, d, -1, 1});
    }
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        // vec.push_back({b, a, i, 1});
        // vec.push_back({a, a, i, -1});

        // vec.push_back({b, n, i, 1});
        // if (a - 1) vec.push_back({a - 1, n, i, -1});
        // if (b - 1) vec.push_back({b, b - 1, i, -1});
        // if ((a - 1) && (b - 1)) vec.push_back({a - 1, b - 1, i, 1});

        vec.push_back({b, a, i, -2});
        vec.push_back({b, n, i, 1});
        vec.push_back({n, a, i, 1});
    }
    sort(vec.begin(), vec.end());
    for (auto [x, y, id, d] : vec) {
        if (id == -1) {
            bit.add(y, d);
        } else {
            ans[id] += d * bit.query(y);
        }
    }
    for (int i = 1; i <= T; i++)
        printf("%d\n", ans[i]);
}